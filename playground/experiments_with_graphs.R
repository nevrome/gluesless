number_of_humans <- 100
number_of_steps <- 10
generation_length <- number_of_humans/number_of_steps

humans <- tibble::tibble(
  human_id = 1:number_of_humans,
  age = as.integer(abs(rnorm(number_of_humans, mean = 0, sd = 30))),
  generation_id = as.integer(ceiling(human_id/generation_length))
)

resample <- function(x, ...) x[sample.int(length(x), ...)]

create_parent_child_connection <- function(x, generation_length) {
  parent_vector <- c()
  child_vector <- c()
  for (parent in 1:nrow(x)) {
    parent_generation_id <- x$generation_id[parent]
    child_generation_id <- parent_generation_id + 1
    if (child_generation_id > max(x$generation_id)) break
    child_pool <- x$human_id[x$generation_id == child_generation_id & !(x$human_id %in% child_vector)]
    if (parent %% generation_length == 0) {
      child <- child_pool
    } else {
      child <- resample(child_pool, sample(ifelse(length(child_pool) < 3, length(child_pool), 3), 1) - 1)
    }
    if (length(child) == 0) next
    parent_vector <- append(parent_vector, rep(parent, length(child)))
    child_vector <- append(child_vector, child)
  }
  tibble::tibble(from = parent_vector, to = child_vector) %>%
    return()
}

humans %>%
  create_parent_child_connection(generation_length) -> hu

# pu <- hu %>% dplyr::filter(
#     !is.na(parent),
#     !is.na(child)
#   ) %>% dplyr::transmute(
#     from = parent,
#     to = child
#   )

hu %>%
 igraph::graph_from_data_frame(d = .) %>%
  visNetwork::toVisNetworkData() %$%
  visNetwork::visNetwork(nodes, edges) %>%
  visNetwork::visNodes(size = 20) %>%
  visNetwork::visHierarchicalLayout(direction = "UD", sortMethod = "directed")
