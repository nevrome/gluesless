library(ggplot2)
library(magrittr)

rsa_hex_df <- hexify(
  areapath = "/home/clemens/nevcloud/geodata/generalshapes/ne_110m_land.shp",
  clippath = "data_raw/extent.shp",
  hexproj  = "+proj=moll +lon_0=0 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs",
  bufferwidth = 2000,
  hexcellsize = 75000
)

ggplot() +
  geom_polygon(
    data = rsa_hex_df,
    aes(
      long,
      lat,
      group = group)
  )

rsa_hex_df %>%
  dplyr::group_by_("id") %>%
  dplyr::summarize_("x" = ~mean(long), "y" = ~mean(lat)) %>%
  dplyr::mutate_(
    "name" = ~seq(from = 0, to = length(id) - 1, by = 1)
  ) %>%
  dplyr::select(name, x, y) -> nodes

######

library(igraph)

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

library(gluesless)

new(
  "model_builder",
  networkland_env = graphwrite(g),
  number_iterations = 30
) %>%
  run() %$%
  idea_exp -> runres

plot_devel(g, runres, store = TRUE)
