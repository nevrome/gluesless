library(magrittr)

load("../neomod_datapool/bronze_age/space_and_network/regions_graph.RData")
load("../neomod_datapool/bronze_age/space_and_network/region_graph_egdes.RData")
load("../neomod_datapool/bronze_age/space_and_network/region_graph_nodes.RData")
load("../neomod_datapool/bronze_age/space_and_network/region_graph_nodes_info.RData")
load("../neomod_datapool/bronze_age/space_and_network/land_outline_sf.RData")

regions <- sf::st_read(
  "../neomod_analysis/manually_changed_data/regionen2017g.shp"
) %>%
  sf::st_transform(4326)

gluesless::plot_world(
  graph = regions_graph,
  world = land_outline,
  regions = regions,
  nodes = nodes,
  plotedges = F
) -> hu

modelobj <- new(
  "model_builder",
  networkland_env = graphwrite(regions_graph),
  number_iterations = 2001
)

runres <- modelobj %>%
  run() %$%
  idea_exp

#plot_world(hex_graph, world = research_area_df, plotedges = TRUE)
states <- link_ideas_world(idea_exp = runres, world_graph = hex_graph)
plot_state(hu, states = states, 100)

#plot_state(hu, states = states, length(states))

# number
runres %>%
  dplyr::group_by(timestep) %>%
  dplyr::summarise(
    alive = mean(num_alive_ideas)
  ) %>%
  ggplot() +
  geom_line(aes(x = timestep, y = alive))

# fecundity
mean_fecu <- runres %>%
  dplyr::group_by(timestep) %>%
  dplyr::summarise(
    mean_fecundity = mean(fecundity)
  )
ggplot() +
  geom_line(data = runres, aes(x = timestep, y = fecundity, group = ideas, colour = ideas)) +
  geom_line(data = mean_fecu, aes(x = timestep, y = mean_fecundity), color = "red")

# power
runres %>%
  dplyr::group_by(timestep) %>%
  dplyr::summarise(
    mean_power = mean(power),
    min_power = min(power),
    max_power = max(power)
  ) %>%
  ggplot() +
  geom_ribbon(aes(
    x = timestep,
    ymin = min_power,
    ymax = max_power
  )) +
  geom_line(aes(x = timestep, y = mean_power), color = "red")

# fidelity
runres %>%
  dplyr::group_by(timestep) %>%
  dplyr::summarise(
    mean_fidelity = mean(fidelity),
    min_fidelity = min(fidelity),
    max_fidelity = max(fidelity)
  ) %>%
  ggplot() +
  geom_ribbon(aes(
    x = timestep,
    ymin = min_fidelity,
    ymax = max_fidelity
  )) +
  geom_line(aes(x = timestep, y = mean_fidelity), color = "red")

# longevity
runres %>%
  dplyr::group_by(timestep) %>%
  dplyr::summarise(
    mean_longevity = mean(longevity),
    min_longevity = min(longevity),
    max_longevity = max(longevity)
  ) %>%
  ggplot() +
  geom_ribbon(aes(
    x = timestep,
    ymin = min_longevity,
    ymax = max_longevity
  )) +
  geom_line(aes(x = timestep, y = mean_longevity), color = "red")
