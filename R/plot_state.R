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

  idea_num_range <- c(0, max(states[[length(states)]]$ideas))

  # plot
  stateplot <- worldplot +
    ggplot2::geom_point(
      data = state,
      ggplot2::aes_string(
        x = "x", y = "y",
        colour = "ideas"
      ),
      #shape = -as.hexmode("2B22"),
      shape = 20,
      size = 3
    ) +
    ggplot2::scale_color_gradient2(
      low = "#218203",
      mid = "#ffff00",
      high = "#990000",
      limits = idea_num_range,
      midpoint = mean(idea_num_range)
    )

  return(stateplot)
}