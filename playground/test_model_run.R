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

#### proportions plot ####

# runres %>%
#   ggplot() +
#   geom_line(
#     aes(x = timestep, y = poison_supply, color = idea)
#   ) +
#   facet_wrap(~region_name) +
#   scale_x_reverse() +
#   theme_bw()

load("../neomod_datapool/bronze_age/space_and_network/proportions_per_region_df.RData")
prop_real <- proportion_per_region_df %>%
  dplyr::filter(
    idea == "cremation" | idea == "inhumation"
  ) %>%
  dplyr::mutate(
    idea = dplyr::case_when(
      idea == "cremation" ~ "cremation_real",
      idea == "inhumation" ~ "inhumation_real"
    )
  )

runres <- modelobj %>%
  run() %$%
  idea_exp

real_plus_model <- runres %>%
  dplyr::full_join(
    y = prop_real
  )

real_plus_model %>%
  ggplot() +
  geom_line(
    aes(x = timestep, y = proportion, color = idea)
  ) +
  facet_wrap(~region_name) +
  scale_x_reverse() +
  theme_bw() +
  scale_color_manual(
    values = c(
      "cremation_real" = "#de2d26",
      "cremation" = "#fc9272",
      "inhumation_real" = "#3182bd",
      "inhumation" = "#9ecae1"
    )
  )


