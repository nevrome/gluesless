#' plot function - world
#'
#' @param graph igraph graph object
#' @param world_polygon polygon data.frame describing the land outline
#' @param hex polygon data.frame describing the hex raster
#' @param nodes data.frame with info about the nodes
#' @param plotedges should the graph edges be plotted?
#'
#' @return resplot
#'
#' @export
plot_world <- function(
  graph, world_polygon, hex = NULL, nodes = NULL, plotedges = FALSE
) {

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

  # plot
  resplot <- ggraph::ggraph(
    graph, layout = 'manual',
    node.positions = vertices
    ) +
    ggplot2::geom_polygon(
      data = world_polygon,
      ggplot2::aes_string(
        x = "long", y = "lat",
        group = "group"
      ),
      fill = NA, colour = "red"
    ) +
    ggplot2::theme_bw() +
    ggplot2::coord_map(
      "ortho", orientation = c(48, 13, 0)
    )

  if (!is.null(hex)) {
    resplot <- resplot + ggplot2::geom_polygon(
      data = hex,
      ggplot2::aes_string(
        x = "long", y = "lat",
        group = "group"
      ),
      fill = NA, colour = "#a0a0a0"
    )
  }

  if (plotedges) {
    resplot <- resplot + ggraph::geom_edge_fan(
      ggplot2::aes_string(edge_alpha = "distance")
    ) +
    ggraph::scale_edge_alpha(
      trans = "reverse"
    )
  }

  if (!is.null(nodes)) {
    nodes_not_empty <- nodes %>%
      dplyr::filter(
        .data$ioi != -1
      )
    resplot <- resplot + ggplot2::geom_point(
      data = nodes_not_empty,
      ggplot2::aes_string(x = "x", y = "y", fill = "ioi"),
      shape = 23,
      size = 3
    )
  }

  return(resplot)
}