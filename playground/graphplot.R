library(igraph)
library(magrittr)
library(gluesless)
library(tidyverse)
library(ggraph)

nodes <- data.frame(
  name = seq(1:20),
  x = runif(20, 0, 100) %>% round(0),
  y = runif(20, 0, 100) %>% round(0)
)

edges <- data.frame(
  from = sample(nodes$name, 30, replace = TRUE),
  to = sample(nodes$name, 30, replace = TRUE),
  distance = runif(30, 0, 100) %>% round(0)
) %>%
  filter(from != to) %>%
  group_by(from, to) %>%
  filter(row_number() == 1)

g <- graph_from_data_frame(
  edges,
  directed = FALSE,
  vertices = nodes
)

g <- set.graph.attribute(g, "graph_name", "testgraph")

new(
  "modell_builder",
  networkland_env = graphwrite(g)
) %>%
  run() %$%
  idea_exp -> runres

plot_devel(g, runres)





