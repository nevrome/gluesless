library(igraph)
library(visNetwork)

#make_tree(10, children = 2, mode = "undirected") %>%
#make_full_graph(10, directed = FALSE, loops = FALSE) %>%
make_ring(30, directed = FALSE, mutual = FALSE, circular = TRUE) %>%
  toVisNetworkData %$%
  visNetwork(nodes, edges) %>%
  visNodes(size = 20)

igraph::from_data_frame()

number_of_humans <- 200

humans <- tibble::tibble(
  id = 1:number_of_humans,
  age = as.integer(abs(rnorm(number_of_humans, mean = 0, sd = 30)))
)

number_of_steps <- 20

number_of_humans/number_of_steps

humans %<>%
  dplyr::mutate(
    generation_id = as.integer(ceiling(id/10)),
    has_parent = FALSE
  )

from <- c()
for (i in 1:number_of_humans) {
  from <- i

  current_generation_id <- humans$generation_id[humans$id == i]
  child_generation <- humans %>%
    dplyr::filter(
      generation_id == current_generation + 1,
      !has_parent
    )

  child <- child_generation$id %>% sample(size = 1)

  humans$has_parent[humans$id == child] <- TRUE

  humans
  child
}


