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

  two_ideas <- unique(state$idea)

  state <- state %>%
    dplyr::select(
      -.data$poison_supply
    ) %>%
    tidyr::spread(.data$idea, .data$proportion) %>%
    dplyr::filter(
      !(.data[[two_ideas[1]]] + .data[[two_ideas[2]]] == 0)
    )

  # plot
  stateplot <- worldplot +
    scatterpie::geom_scatterpie(
      data = state,
      ggplot2::aes_string(x = "x", y = "y", group = "name"),
      cols = two_ideas
    ) +
    ggplot2::ggtitle(paste0(state$timestep[1], "calBC"))

  return(stateplot)
}