load("../popgenerator/testresults/pop.RData")
load("../popgenerator/testresults/rel.RData")

g <- igraph::graph_from_data_frame(
  rel %>% dplyr::filter(from <= max(pop$id), to <= max(pop$id)),
  directed = FALSE,
  vertices = pop %>% dplyr::select(id, dplyr::everything())
)

igraph::write_graph(g, file = "data_raw/test.graphml", format = "graphml")

#hu <- graphwrite(g)

modelobj <- new(
  "model_builder",
  networkland_env = "data_raw/test.graphml",
  number_iterations = 2001,
  ideas_list = c("a", "b"),
  ideas_proportions_matrix = matrix(c(1,2,3,4),2)
)

run(modelobj)

