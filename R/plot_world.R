#' plot function - world
#'
#' @param graph igraph graph object
#' @param world_polygon polygon data.frame describing the land outline
#' @param regions polygon data.frame describing the regions
#' @param nodes data.frame with info about the nodes
#' @param plotedges should the graph edges be plotted?
#'
#' @return resplot
#'
#' @export
plot_world <- function(
  graph, world_polygon, regions = NULL, nodes = NULL, plotedges = TRUE
) {

  # extract vertices table from igraph object
  vertices <- igraph::get.vertex.attribute(graph) %>%
    as.data.frame(stringsAsFactors = FALSE) %>%
    dplyr::mutate_("name" = ~as.numeric(name))

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
      fill = NA, colour = "black"
    ) +
    ggplot2::theme_bw() +
    ggplot2::coord_map(
      #"ortho", orientation = c(48, 13, 0)
      "mercator"
    )

  if (!is.null(regions)) {
    resplot <- resplot + ggplot2::geom_polygon(
      data = regions,
      ggplot2::aes_string(
        x = "long", y = "lat",
        group = "group"
      ),
      fill = NA, colour = "red"
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
    nodes_not_empty <- nodes #%>%
      #dplyr::filter(
      #  .data$ioi != -1
      #)
    resplot <- resplot + ggplot2::geom_point(
      data = nodes_not_empty,
      ggplot2::aes_string(x = "x", y = "y"),
      #ggplot2::aes_string(x = "x", y = "y", fill = "ioi"),
      shape = 23,
      size = 3
    )
  }

  return(resplot)
}