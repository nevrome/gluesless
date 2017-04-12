library(ggplot2)
library(magrittr)

area <- rgdal::readOGR(
  dsn = "/home/clemens/nevcloud/geodata/generalshapes/ne_110m_land.shp"
)

research_area_border <- rgdal::readOGR(
  dsn = "data_raw/extent.shp"
)

research_area <- rgeos::gIntersection(
  area, research_area_border, byid = TRUE,
  drop_lower_td = TRUE
)

rsa_df <- ggplot2::fortify(research_area)

rsa_hex_df <- hexify(
  area = research_area,
  hexproj  = "+proj=moll +lon_0=0 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs",
  bufferwidth = 2000,
  hexcellsize = 75000
  ) %>%
  ggplot2::fortify(region = "id")

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

plot_devel(g, runres, store = TRUE, world = rsa_df, hex = rsa_hex_df)
