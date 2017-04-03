library(igraph)
library(magrittr)
library(gluesless)

test <- graphtest()

graphread(test) %>%
  plot()

#####

library(igraph)
library(magrittr)
library(gluesless)

actors <- data.frame(
  name = c("Alice", "Bob", "Cecil", "David", "Esmeralda")
)

relations <- data.frame(
  from = c("Bob", "Cecil", "Cecil", "David", "David", "Esmeralda"),
  to = c("Alice", "Bob", "Alice", "Alice", "Bob", "Alice"),
  distance = c(101, 102, 103, 104, 105, 106)
)

g <- graph_from_data_frame(
  relations,
  directed = FALSE,
  vertices = actors
)

g <- set.graph.attribute(g, "graph_name", "testgraph")

hununu <- graphwrite(g)

#####

test_builder <- new(
  "modell_builder",
  networkland_env = hununu
)

run(test_builder) -> flut
#
# library(ggraph)
#
# n1 <- length(flut$idea_timesteps$identity)
#
# tidy <- data.frame()
#
# for (p1 in 1:n1) {
#   t <- flut$idea_timesteps$identity
#   n2 <- length(t[[p1]])
#   for (p2 in 1: n2) {
#     tidy[]
#   }
# }


