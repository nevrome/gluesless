#' @export
find_starting_pos <- function(nodes, lon_start, lat_start, n) {

  res <- nodes %>%
    dplyr::mutate(
      long_dist = abs(x - lon_start),
      lat_dist = abs(y - lat_start)
    ) %>%
    dplyr::mutate(
      geo_dist = long_dist + lat_dist
    ) %>%
    dplyr::arrange(
      geo_dist
    ) %>%
    head(n) %$%
    name

  return(res)
}