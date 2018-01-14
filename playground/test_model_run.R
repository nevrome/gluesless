library(magrittr)

#### load data ####
load("../neomod_datapool/bronze_age/space_and_network/regions_graph.RData")
load("../neomod_datapool/bronze_age/space_and_network/region_graph_egdes.RData")
load("../neomod_datapool/bronze_age/space_and_network/region_graph_nodes.RData")
load("../neomod_datapool/bronze_age/space_and_network/region_graph_nodes_info.RData")
load("../neomod_datapool/bronze_age/space_and_network/land_outline_sf.RData")

regions <- sf::st_read(
  "../neomod_analysis/manually_changed_data/regionen2017g.shp"
) %>%
  sf::st_transform(4326)

#### prepare data ####
start_situation <- nodes_info$`2500` %>%
  dplyr::filter(
    idea == "cremation" | idea == "inhumation"
  )

start_situation_reduced <- start_situation %>%
  dplyr::select(region_name, idea, proportion) %>%
  tidyr::spread(idea, proportion) %>%
  dplyr::arrange(match(region_name, start_situation$region_name))

ideas <- colnames(start_situation_reduced)[-1]
ideas_proportions <- start_situation_reduced[, -1] %>% as.matrix()

#### prepare and run model ####
modelobj <- new(
  "model_builder",
  networkland_env = graphwrite(regions_graph),
  number_iterations = 2001,
  ideas_list = ideas,
  ideas_proportions_matrix = ideas_proportions
)

runres <- modelobj %>%
  run() %$%
  idea_exp

#### plot ####
states <- link_ideas_world(idea_exp = runres, world_graph = regions_graph)

gluesless::plot_world(
  graph = regions_graph,
  world = land_outline,
  regions = regions,
  nodes = nodes,
  plotedges = F
) %>%
  plot_state(states = states, 2001)
