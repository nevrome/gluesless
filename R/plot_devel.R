plot_devel <- function(graph, runres, path = "../modevel/") {

  do.call(file.remove, list(list.files(path, full.names = TRUE)))

  vertices <- igraph::get.vertex.attribute(graph) %>%
    as.data.frame(stringsAsFactors = FALSE) %>%
    mutate(name = as.numeric(name))

  minx = min(vertices$x - 2)
  maxx = max(vertices$x + 2)
  miny = min(vertices$y - 2)
  maxy = max(vertices$y + 2)

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
        size = (maxx-minx)*1/23,
        fill = "white"
      ) +
      geom_node_text(
        aes(label = name),
        size = (maxx-minx)*1/32
      ) +
      geom_jitter(
        data = res,
        aes(
          x = x, y = y,
          fill = ideas,
          colour = n
        ),
        shape = 21,
        size = (maxx-minx)*1/40,
        stroke = 1.5,
        width = (maxx-minx)*1/30,
        height = (maxx-minx)*1/30
      ) +
      scale_color_continuous(
        low = "#e6e6e6",
        high = "#000000",
        limits = c(1, 10)
      ) +
      scale_fill_gradient2(
        low = "#ffffff",
        mid = "#ffff00",
        high = "#990000",
        limits = c(0, 100),
        midpoint = 50
      ) +
      theme_bw() +
      xlim(minx, maxx) +
      ylim(miny, maxy)


    ggsave(
      filename = paste0(path, i),
      plot = graphplot,
      device = "png",
      width = 300,
      height = 200,
      units = "mm",
      dpi = 300
    )
  }
}