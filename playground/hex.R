library(ggplot2)
library(magrittr)
library(igraph)

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

nodes_spdf <- SpatialPointsDataFrame(
  coords = dplyr::select_(nodes, "x", "y"), data = nodes,
  proj4string = CRS("+proj=longlat +datum=WGS84 +ellps=WGS84 +towgs84=0,0,0")
) %>% sp::spTransform(
  sp::CRS("+proj=moll +lon_0=0 +x_0=0 +y_0=0 +ellps=WGS84 +datum=WGS84 +units=m +no_defs")
)

distmat <- rgeos::gDistance(nodes_spdf, byid = TRUE)

edges <- apply(distmat, 1, function(x) {
  order(x, decreasing=F)[c(2:7)] - 1
  }) %>% t %>%
  as.data.frame() %>%
  set_names(paste0("n_", 1:6)) %>%
  dplyr::mutate(nodes = as.numeric(row.names(.)) - 1) %>%
  tidyr::gather(
    ., key = schnupp, value = neighs,
    n_1, n_2, n_3, n_4, n_5, n_6
  ) %>%
  dplyr::select(nodes, neighs) %>%
  dplyr::rename(from = nodes, to = neighs) %>%
  dplyr::mutate(distance = runif(nrow(.), 0, 100) %>% round(0))

#####

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

plot_world(g, world = rsa_df, hex = rsa_hex_df)
plot_world(g, world = rsa_df, plotedges = TRUE)

plot_devel(g, runres, store = TRUE, world = rsa_df, hex = rsa_hex_df)
