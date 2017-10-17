library(gluesless)
library(magrittr)

load("/home/clemens/neomod/neomod_datapool/model_data/hex_graph.RData")
load("/home/clemens/neomod/neomod_datapool/model_data/research_area_df.RData")
load("/home/clemens/neomod/neomod_datapool/model_data/research_area_hex_df.RData")
load("/home/clemens/neomod/neomod_datapool/model_data/hex_graph_nodes.RData")


modelobj <- new(
  "model_builder",
  networkland_env = graphwrite(hex_graph),
  number_iterations = 10,
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

