library(igraph)
library(visNetwork)

#make_tree(10, children = 2, mode = "undirected") %>%
#make_full_graph(10, directed = FALSE, loops = FALSE) %>%
make_ring(30, directed = FALSE, mutual = FALSE, circular = TRUE) %>%
  toVisNetworkData %$%
  visNetwork(nodes, edges) %>%
  visNodes(size = 20)

number_of_humans <- 200
number_of_steps <- 20
generation_length <- number_of_humans/number_of_steps

humans <- tibble::tibble(
  human_id = 1:number_of_humans,
  age = as.integer(abs(rnorm(number_of_humans, mean = 0, sd = 30))),
  generation_id = as.integer(ceiling(human_id/generation_length)),
  parent = NA_integer_,
  child = NA_integer_
)

create_parent_child_connection <- function(x) {
  for (parent in 1:nrow(x)) {
    parent_generation_id <- x$generation_id[parent]
    child_generation_id <- parent_generation_id + 1
    if (child_generation_id > max(x$generation_id)) break
    child_pool <- x$human_id[x$generation_id == child_generation_id & is.na(x$parent)]
    child <- ifelse(length(child_pool) > 1, sample(child_pool, 1), child_pool)
    x$child[parent] <- child
    x$parent[child] <- parent
  }
  return(x)
}

humans %>%
  create_parent_child_connection() -> hu

pu <- hu %>% dplyr::filter(
    !is.na(parent),
    !is.na(child)
  ) %>% dplyr::transmute(
    from = parent,
    to = child
  )

pu %>%
 igraph::graph_from_data_frame(d = .) %>%
  visNetwork::toVisNetworkData() %$%
  visNetwork::visNetwork(nodes, edges) %>%
  visNetwork::visNodes(size = 20)
