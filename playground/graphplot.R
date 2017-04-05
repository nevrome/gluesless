library(igraph)
library(magrittr)
library(gluesless)
library(ggplot2)
library(ggraph)
library(dplyr)

actors <- data.frame(
  name = seq(1:5),
  x = c(2.5,3,1,4,3),
  y = c(2.5,4,5,2,1)
)

relations <- data.frame(
  from = c(2, 3, 3, 4, 4, 5),
  to = c(1, 2, 1, 1, 2, 1),
  distance = c(101, 102, 103, 104, 105, 106)
)

g <- graph_from_data_frame(
  relations,
  directed = FALSE,
  vertices = actors
)

g <- set.graph.attribute(g, "graph_name", "testgraph")

new(
  "modell_builder",
  networkland_env = graphwrite(g)
) %>% run()

x <- data.frame(id = NA, nodes = NA)

for (i in 1:10) {
  runif(1, 1, 10) %>% round(0) -> x[i,]$id
  runif(1, 1, 5) %>% round(0) -> x[i,]$nodes
}

res <- dplyr::left_join(
  actors, x, by = c("name" = "nodes")) %>%
  group_by(id) %>%
  mutate(n = n()) %>%
  as.data.frame()

ggraph(g, layout = 'manual', node.positions = actors) +
  geom_edge_fan() +
  geom_node_point(
    shape = 21,
    size = 5,
    fill = "white"
  ) +
  geom_node_text(aes(label = name)) +
  geom_jitter(
    data = res,
    aes(
      x = x, y = y,
      fill = id,
      colour = n
    ),
    shape = 21,
    size = 4,
    stroke = 2,
    width = 0.2,
    height = 0.2
  ) +
  scale_color_continuous(
    low = "#808080",
    high = "#000000"
  ) +
  scale_fill_continuous(
    low = "#33ff33",
    high = "#003300"
  ) +
  theme_bw()


