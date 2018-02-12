#' generate
#'
#' @param t double time
#' @param n integer amount of humans to generate
#' @param start_id integer id of first generated human. default = 1
#' @param start_age integer current age of humans. default: NA (current ages are generated)
#' @param unit_vector test
#'
#' @return tibble with humans
#'
#' @export
generate_humans <- function(
  t,
  n,
  start_id = 1,
  start_age = NA,
  unit_vector
) {
  ages <- get_ages(t, n)

  tibble::tibble(
    id =          get_id_range(start_id, n),
    current_age = get_current_age(start_age, ages),
    death_age =   get_death_age(ages),
    dead =        FALSE,
    birth_time =  get_birth_time(t, current_age),
    death_time =  get_death_time(t, death_age, current_age),
    sex =         get_sexes(t, n),
    #unit = population_unit_distribution(t)(number, unit_vector),
    unit_dead = FALSE
  ) %>% return()
}

get_id_range <- function(start_id, n) {
  start_id:(start_id + n - 1)
}

get_current_age <- function(start_age, ages) {
  if (is.na(start_age)) {ages} else {start_age}
}

get_death_age <- function(ages) {
  ages + resample(0:10, length(ages), replace = TRUE)
}

get_birth_time <- function(t, current_age) {
  t - current_age
}

get_death_time <- function(t, death_age, current_age) {
  t + (death_age - current_age)
}
