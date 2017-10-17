#' test
#'
#' test
#'
#' @param nodes test
#' @param lon_start test
#' @param lat_start test
#' @param n test
#'
#' @return test
#'
#' @export
find_starting_pos <- function(nodes, lon_start, lat_start, n) {

  res <- nodes %>%
    dplyr::mutate(
      long_dist = abs(.data$x - lon_start),
      lat_dist = abs(.data$y - lat_start)
    ) %>%
    dplyr::mutate(
      geo_dist = .data$long_dist + .data$lat_dist
    ) %>%
    dplyr::arrange(
      .data$geo_dist
    ) %>%
    utils::head(n)

  return(res$name)
}