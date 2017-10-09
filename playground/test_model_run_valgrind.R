# R -d "valgrind --leak-check=full --show-reachable=yes" -f test_model_run.R

library(gluesless)
library(magrittr)

load("/home/clemens/neomod/neomod_datapool/model_data/hex_graph.RData")
load("/home/clemens/neomod/neomod_datapool/model_data/research_area_df.RData")
load("/home/clemens/neomod/neomod_datapool/model_data/research_area_hex_df.RData")

modelobj <- new(
  "model_builder",
  networkland_env = graphwrite(hex_graph),
  number_iterations = 10,
  initial_idea_starting_positions = c(2824, 2825, 2826, 2773, 2774, 2775, 2712, 2713, 2714)
)

runres <- modelobj %>%
  run() %$%
  idea_exp
