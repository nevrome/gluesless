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

run(test_builder) #-> fluut
#
# fluut %>% graphread() -> h
#
# summary(g)
# summary(h)
# plot(g)
# plot(h)
#
# #####
#
#
