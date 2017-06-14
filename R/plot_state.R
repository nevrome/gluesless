#' plot function - add ideas to world plot
#'
#' @param worldplot ggplot world plot
#' @param states result df of link_ideas_world
#' @param state_id integer. id of state to plot
#'
#' @return resplot
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
      shape = 20
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