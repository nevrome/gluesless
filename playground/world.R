library(igraph)
library(magrittr)
library(gluesless)
library(tidyverse)
library(ggraph)

regions <- read.table("playground/region.txt", sep = "\t", header = TRUE)

nodes <- regions %>%
  group_by(region) %>%
  summarise(x = mean(lon), y = mean(lat)) %>%
  filter(region != -2147483648) %>%
  filter(x < 50 & x > -11 & y > 25 & y < 75) %>%
  mutate(name = seq(0, nrow(.) - 1)) %>%
  select(name, x, y) %>%
  transform(name = as.numeric(name))

edges <- data.frame(
  from = sample(nodes$name, 30, replace = TRUE),
  to = sample(nodes$name, 30, replace = TRUE),
  distance = runif(30, 0, 100) %>% round(0)
)

g <- graph_from_data_frame(
  edges,
  directed = FALSE,
  vertices = nodes
) %>%
  igraph::simplify(
    edge.attr.comb = "mean"
  )

g <- set.graph.attribute(g, "graph_name", "testgraph")

new(
  "model_builder",
  networkland_env = graphwrite(g),
  number_iterations = 10
) %>%
  run() %$%
  idea_exp -> runres

plot_devel(g, runres, store = TRUE)
