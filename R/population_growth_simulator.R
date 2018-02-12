#### main function ####

#' @export
simulate_growth <- function(humans, time = 1:2000) {

  unit_counter <- humans %>% get_last_established_unit()

  pb <- txtProgressBar(style = 3)
  for (t in time) {
    setTxtProgressBar(pb, t/length(time))

    humans %<>% find_and_realize_deaths()
    necessary_births <- humans %>% calculate_amount_of_necessary_births(t)
    if (necessary_births <= 0) next

    units <- humans %>% get_currently_alive_units()
    units_target_amount <- unit_amount(t)

    if (length(units) > units_target_amount) {
      new_unit_vector <- resample(units, units_target_amount)
      humans %>% realize_unit_deaths(new_unit_vector)
    } else {
      difference <- units_target_amount - length(units)
      new_unit_vector <- c(units, (unit_counter + 1):(unit_counter + difference + 1))
      unit_counter <- unit_counter + difference
    }

    humans %<>% rbind(
      generate_humans(
        t = t,
        n = necessary_births,
        start_id = max(humans$id + 1),
        start_age = 0,
        unit_vector = new_unit_vector
      )
    )
  }
  close(pb)

  return(humans)
}

find_and_realize_deaths <- function(humans) {
  humans[!humans$dead, ] %<>%
    dplyr::mutate(
      current_age = as.integer(current_age + 1),
      dead = current_age >= death_age
    )
  return(humans)
}

realize_unit_deaths <- function(humans, new_unit_vector) {
  humans[!humans$unit_dead, ] %<>%
    dplyr::mutate(
      unit_dead = ifelse(unit_dead %in% new_unit_vector, FALSE, TRUE)
    )
  return(humans)
}

get_amount_of_living_humans <- function(humans) {
  sum(!humans$dead)
}

calculate_amount_of_necessary_births <- function(humans, t) {
  round(population_size(t) - get_amount_of_living_humans(humans), 0)
}

get_currently_alive_units <- function(humans) {
  unique(humans$unit[!humans$unit_dead])
}

get_last_established_unit <- function(humans) {
  max(humans$unit)
}
