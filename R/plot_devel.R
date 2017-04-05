plot_devel <- function(graph, runres, path = "../modevel/") {

  vertices <- igraph::get.vertex.attribute(graph) %>%
    as.data.frame(stringsAsFactors = FALSE) %>%
    mutate(name = as.numeric(name))

  timelist <- plyr::dlply(runres, "timestep", identity)

  for (i in 1:length(timelist)) {

    res <- dplyr::inner_join(
      vertices, timelist[[i]], by = c("name" = "vertices")) %>%
      group_by(ideas) %>%
      mutate(n = n()) %>%
      as.data.frame()

    graphplot <- ggraph(graph, layout = 'manual', node.positions = vertices) +
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
          fill = ideas,
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

    ggsave(filename = paste0(path, i), graphplot, device = "png")
  }
}