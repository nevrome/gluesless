library(gluesless)
library(magrittr)

load("/home/clemens/neomod/neomod_datapool/model_data/hex_graph.RData")
load("/home/clemens/neomod/neomod_datapool/model_data/research_area_df.RData")
load("/home/clemens/neomod/neomod_datapool/model_data/research_area_hex_df.RData")
load("/home/clemens/neomod/neomod_datapool/model_data/hex_graph_nodes.RData")


modelobj <- new(
  "model_builder",
  networkland_env = graphwrite(hex_graph),
  number_iterations = 500,
  initial_idea_starting_positions = find_starting_pos(
    nodes, 38.923622, 36.067470, 3
  )
)

runres <- modelobj %>%
  run() %$%
  idea_exp

#runres$number_of_ideas

#plot_world(hex_graph, world = research_area_df, plotedges = TRUE)

plot_world(hex_graph, world = research_area_df, hex = research_area_hex_df, plotedges = F) -> hu
#hu2 <- ggplot2::ggplotGrob(hu)
states <- link_ideas_world(idea_exp = runres, world_graph = hex_graph)

plot_state(hu, states = states, length(states))

library(dplyr)
library(ggplot2)

# number
runres %>%
  dplyr::group_by(timestep) %>%
  dplyr::summarise(
    alive = mean(num_alive_ideas)
  ) %>%
  ggplot() +
  geom_line(aes(x = timestep, y = alive))

# fecundity
runres %>%
  ggplot() +
  geom_line(aes(x = timestep, y = fecundity, group = ideas, colour = ideas))

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
