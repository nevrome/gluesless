#' generate vertical relations
#'
#' @param settings test
#'
#' @return huup
#'
#' @export
generate_vertical_relations <- function(settings) {

  population <- settings@population

  from <- c()
  to <- c()
  type <- c()
  start_time <- c()
  end_time <- c()

  population$previous_partner <- NA

  pb <- utils::txtProgressBar(style = 3)
  for (child in 1:nrow(population)) {

    potential_parents <- get_potential_parents(population, child, settings)
    monogamous <- is_monogamous(settings)

    # check if there is a potential pair to make a child
    # else the child has no parents
    if (!all(c("male", "female") %in% unique(potential_parents$sex))) {next}

    # randomly select partner1
    partner1_df <- potential_parents %>%
      dplyr::sample_n(1)

    if(
      # check if partner1 already has a previous partner
      !is.na(partner1_df$previous_partner) &&
      # check if the previous partner is in the right age for another child
      partner1_df$previous_partner %in% potential_parents$id &&
      # check if partner1 behaves monogamous
      monogamous
    ) {
      # the previous partner becomes also the parent of this child
      partner2_df <- population[partner1_df$previous_partner, ]
    } else {
      # a new partner is selected
      partner2_df <- select_new_partner(potential_parents, partner1_df)
    }

    population$previous_partner[partner1_df$id] <- partner2_df$id
    population$previous_partner[partner2_df$id] <- partner1_df$id


    partner1 <- partner1_df$id
    partner2 <- partner2_df$id

    from <- append(
      from, c(
        partner1,
        partner1,
        partner2
      )
    )
    to <- append(
      to, c(
        partner2,
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
    utils::setTxtProgressBar(pb, child/nrow(population))
  }
  close(pb)

  vertical_relations <- tibble::tibble(from, to, type)

  return(vertical_relations)

}

#### helper functions ####

is_monogamous <- function(settings) {
  stats::runif(1,0,1) <= settings@monogamy_probability
}

get_potential_parents <- function(population, child, settings) {
  population %>%
    dplyr::filter(
      .data$unit == population$unit[child]
    ) %>%
    dplyr::filter(
      (.data$birth_time + settings@start_fertility_age) <= population$birth_time[child],
      population$birth_time[child] <= (.data$birth_time +  settings@stop_fertility_age)
  )
}

select_new_partner <- function(potential_parents, partner1_df) {
  potential_parents %>%
    dplyr::filter(.data$sex != partner1_df$sex) %>%
    dplyr::sample_n(1)
}


