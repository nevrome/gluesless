#' generate vertical relations
#'
#' @param settings test
#'
#' @return huup
#'
#' @export
generate_vertical_relations <- function(population) {

  from <- c()
  to <- c()
  type <- c()
  start_time <- c()
  end_time <- c()

  pb <- txtProgressBar(style = 3)
  for (child in 1:nrow(population)) {
    potential_parents <- population %>% dplyr::filter(
      (birth_time + 12) <= population$birth_time[child],
      population$birth_time[child] <= (birth_time + 60),
      unit == population$unit[child]
    )
    if (!all(c("male", "female") %in% unique(potential_parents$sex))) {next}
    mother <- potential_parents %>%
      dplyr::filter(sex == "female") %>%
      dplyr::sample_n(1) %$%
      id
    father <- potential_parents %>%
      dplyr::filter(sex == "male") %>%
      dplyr::sample_n(1) %$%
      id
    from <- append(
      from, c(
        mother,
        mother,
        father
      )
    )
    to <- append(
      to, c(
        father,
        child,
        child
      )
    )
    type <- append(
      type, c(
        "sexing",
        "child_of",
        "child_of"
      )
    )
    #label <- append(label, c("❤", "✌", "✌"))
    start_time <- append(
      start_time, c(
        population$birth_time[child] - 1,
        population$birth_time[child],
        population$birth_time[child]
      )
    )
    end_time <- append(
      end_time, c(
        population$birth_time[child] + 2,
        population$birth_time[child] + 14,
        population$birth_time[child] + 14
      )
    )
    setTxtProgressBar(pb, child/nrow(population))
  }
  close(pb)

  vertical_relations <- tibble::tibble(from, to)

  return(vertical_relations)

}