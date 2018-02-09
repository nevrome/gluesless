number_of_humans <- 50
number_of_steps <- 5
generation_length <- number_of_humans/number_of_steps

humans <- tibble::tibble(
  human_id = 1:number_of_humans,
  age = as.integer(abs(rnorm(number_of_humans, mean = 0, sd = 30))),
  generation_id = as.integer(ceiling(human_id/generation_length)),
  group = generation_id,
  sex = rep(c("male", "female"), number_of_humans/2),
  shape = ifelse(sex == "male", "triangle", "triangleDown")
)

resample <- function(x, ...) x[sample.int(length(x), ...)]

heavy_sexing <- function(x) {
  from <- c()
  to <- c()
  for (current_human in 1:nrow(x)) {
    if (current_human %in% c(from, to)) next
    current_generation <- x$generation_id[current_human]
    current_sex <- x$sex[current_human]
    potential_partners <- x$human_id[
      x$generation_id == current_generation &
        x$sex != current_sex &
        !(x$human_id %in% c(from, to))
    ]
    if (length(potential_partners) == 0) next
    partner <- resample(potential_partners, 1)
    from <- append(from, current_human)
    to <- append(to, partner)
  }
  tibble::tibble(from, to, label = "❤")
}

humans %>%
  heavy_sexing() -> sexing

sexing %>%
  igraph::graph_from_data_frame(d = .) %>%
  visNetwork::toVisNetworkData() %$%
  visNetwork::visNetwork(nodes, edges) %>%
  visNetwork::visNodes(size = 20)

create_parent_child_connection <- function(x, generation_length, sexing) {
  from <- c()
  to <- c()
  for (parent in 1:nrow(x)) {
    parent_generation_id <- x$generation_id[parent]
    child_generation_id <- parent_generation_id + 1
    if (child_generation_id > max(x$generation_id)) break
    child_pool <- x$human_id[x$generation_id == child_generation_id & !(x$human_id %in% to)]
    if (parent %% generation_length == 0) {
      child <- child_pool
    } else {
      child <- resample(child_pool, sample(ifelse(length(child_pool) < 3, length(child_pool), 3), 1) - 1)
    }
    if (length(child) == 0) next
    from <- append(from, rep(parent, length(child)))
    to <- append(to, child)
    partner <- c(sexing$from[sexing$to == parent], sexing$to[sexing$from == parent])
    from <- append(from, rep(partner, length(child)))
    to <- append(to, child)
  }
  tibble::tibble(from, to, label = "✌")
}

humans %>%
  create_parent_child_connection(generation_length, sexing) -> kidding

# pu <- hu %>% dplyr::filter(
#     !is.na(parent),
#     !is.na(child)
#   ) %>% dplyr::transmute(
#     from = parent,
#     to = child
#   )

rbind(
  sexing, kidding
) -> network

network %>%
 igraph::graph_from_data_frame(d = ., vertices = humans) %>%
  visNetwork::toVisNetworkData() %$%
  visNetwork::visNetwork(nodes, edges) %>%
  visNetwork::visGroups() %>%
  visNetwork::visNodes(size = 20) #%>%
  #visNetwork::visHierarchicalLayout(direction = "UD", sortMethod = "directed")
