library(igraph)
library(visNetwork)

#make_tree(10, children = 2, mode = "undirected") %>%
#make_full_graph(10, directed = FALSE, loops = FALSE) %>%
make_ring(30, directed = FALSE, mutual = FALSE, circular = TRUE) %>%
  toVisNetworkData %$%
  visNetwork(nodes, edges) %>%
  visNodes(size = 20)
