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

  state <- state %>%
    dplyr::mutate(
      "xleft" = .data$x - 1,
      "xright" = .data$x + 1
    )

  state_burial_type <- state %>%
    dplyr::select(
      -.data$flat, -.data$mound
    ) %>%
    dplyr::filter(
      !(.data$inhumation + .data$cremation == 0)
    )

  state_burial_structure <- state %>%
    dplyr::select(
      -.data$inhumation, -.data$cremation
    ) %>%
    dplyr::filter(
      !(.data$flat + .data$mound == 0)
    )

  # plot
  stateplot <- worldplot +
    scatterpie::geom_scatterpie(
      data = state_burial_type,
      ggplot2::aes_string(x = "xleft", y = "y", group = "name"),
      cols = c("inhumation", "cremation")
    ) +
    scatterpie::geom_scatterpie(
      data = state_burial_structure,
      ggplot2::aes_string(x = "xright", y = "y", group = "name"),
      cols = c("flat", "mound")
    ) +
    ggplot2::ggtitle(paste0(state$timestep[1], "calBC"))

  return(stateplot)
}