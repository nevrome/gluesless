#' plot function
#'
#' @description
#' huhn
#'
#' @param test igraph graph object
#'
#' @return fnuc
#'
#' @export
plot_state <- function(worldplot, states, state_id) {

  state <- states[[state_id]]

  # plot
  stateplot <- worldplot +
    ggplot2::geom_jitter(
      data = state,
      ggplot2::aes_string(
        x = "x", y = "y",
        colour = "ideas"
      ),
      shape = 20,
      # size = mext*1/30,
      # width = extx*1/200,
      # height = exty*1/200
    ) +
    ggplot2::scale_color_gradient2(
      low = "#218203",
      mid = "#ffff00",
      high = "#990000",
      limits = c(0, 100),
      midpoint = 50
    )

  return(stateplot)
}