load("../popgenerator/testresults/pop.RData")
load("../popgenerator/testresults/rel.RData")

g <- igraph::graph_from_data_frame(
  rel %>% dplyr::filter(from <= max(pop$id), to <= max(pop$id)),
  directed = FALSE,
  vertices = pop %>% dplyr::select(id, dplyr::everything())
)

hu <- graphwrite(g)

igraph::write_graph(g, file = "data_raw/test.graphml", format = "graphml")
