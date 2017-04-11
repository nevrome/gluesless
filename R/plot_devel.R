#' plot function - network development
#'
#' @description
#' Creates graph plots for a model run.
#'
#' @param graph igraph graph object
#' @param runres runres dataframe with columns timestep, ideas, vertices
#' @param store switch to decide, if the plots should be stored in the
#'              file system. Default: FALSE
#' @param path directory in file system, where the plots are stored.
#'             \bold{Other files in this directory are deleted.}
#'             Default: "../modevel/"
#'
#' @return NULL - just called for side effects
#'
#' @export
plot_devel <- function(
  graph, runres, store = FALSE, path = "../modevel/"
) {

  # check if runres is empty
  if (nrow(runres) == 0) {
    return(NULL)
  }

  # extract vertices table from igraph object
  vertices <- igraph::get.vertex.attribute(graph) %>%
    as.data.frame(stringsAsFactors = FALSE) %>%
    dplyr::mutate_("name" = ~as.numeric(name))

  # calculate extend of graph
  minx = min(vertices$x)
  maxx = max(vertices$x)
  miny = min(vertices$y)
  maxy = max(vertices$y)

  extx = maxx - minx
  exty = maxy - miny
  mext = min(c(extx, exty))

  minx = minx - extx/10
  maxx = maxx + extx/10
  miny = miny - exty/10
  maxy = maxy + exty/10

  # separate timesteps into a list
  timelist <- plyr::dlply(runres, "timestep", identity)

  # create plots for each timestep
  plotlist <- list()
  for (p1 in 1:length(timelist)) {

    # prepare data.frame for individual timestep
    res <- dplyr::inner_join(
      vertices, timelist[[p1]], by = c("name" = "vertices")) %>%
      dplyr::group_by_("ideas") %>%
      dplyr::mutate_("n" = ~n()) %>%
      as.data.frame()

    # load world map
    world <- ggplot2::map_data("world")

    # plot
    plotlist[[p1]] <- ggraph::ggraph(
      graph, layout = 'manual',
      node.positions = vertices
      ) +
      ggplot2::geom_polygon(
        data = world,
        ggplot2::aes_string(
         x = "long", y = "lat",
         group = "group"
        ),
        fill = "#ffffff", colour = "#a0a0a0"
      ) +
      ggraph::geom_edge_fan(
        ggplot2::aes_string(edge_alpha = "distance")
      ) +
      ggraph::scale_edge_alpha(trans = "reverse") +
      ggraph::geom_node_point(
        shape = 21,
        size = mext*1/23,
        fill = "white"
      ) +
      ggraph::geom_node_text(
        ggplot2::aes_string(label = "name"),
        size = mext*1/32
      ) +
      ggplot2::geom_jitter(
        data = res,
        ggplot2::aes_string(
          x = "x", y = "y",
          fill = "ideas",
          colour = "n"
        ),
        shape = 21,
        size = mext*1/30,
        stroke = 1,
        width = extx*1/35,
        height = exty*1/35
      ) +
      ggplot2::scale_color_continuous(
        low = "#e6e6e6",
        high = "#000000",
        limits = c(1, 100)
      ) +
      ggplot2::scale_fill_gradient2(
        low = "#218203",
        mid = "#ffff00",
        high = "#990000",
        limits = c(0, 100),
        midpoint = 50
      ) +
      ggplot2::theme_bw() +
      ggplot2::xlim(minx, maxx) +
      ggplot2::ylim(miny, maxy) +
      ggplot2::coord_map(
        "ortho", orientation = c(48, 9, 0)
        # xlim = c(minx, maxx),
        # ylim = c(miny, maxy)
      )
  }

  # user triggered plots
  if (!store) {
    for (p3 in 1:length(plotlist)) {
      plotlist[[p3]] %>% ggplot2::ggplot()
      readline(prompt="Press [enter] to continue with the next plot.")
    }
  }

  # store plots in filesystem
  if (store) {
    do.call(file.remove, list(list.files(path, full.names = TRUE)))
    for(p2 in 1:length(plotlist)) {
      ggplot2::ggsave(
        filename = paste0(path, p2),
        plot = plotlist[[p2]],
        device = "png",
        width = 300,
        height = 200,
        units = "mm",
        dpi = 300
      )
    }
  }

  return(NULL)
}