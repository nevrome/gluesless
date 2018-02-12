#' population size at time
#'
#' @param t double time
#'
#' @return integer population size at t
#'
#' @export
population_size <- function(t) {
  round((cos(0.01 * t) + 3) * 100 + 0.2 * t, 0)
}

#' population age distribution at time
#'
#' @param t double time
#'
#' @return distribution function
#'
#' @export
age_distribution <- function(t) {
  # currently no time dependend development
  function(x) {
    1 / (1 + 0.0004 * 0.7^(-7*log(x)))
  }
  #plot(0:100, population_age_distribution_at_time(0)(0:100))
}

#' get n ages according to age distribution at time
#'
#' @param t double time
#' @param n integer amount
#'
#' @return vector of ages
#'
#' @export
get_ages <- function(t, n) {
  # get distribution function
  distribution_function <- age_distribution(t)
  # define possible age range
  age_range <- 0:100
  # draw sample
  sample(age_range, size = n, replace = TRUE, prob = distribution_function(age_range))
}

#' population sex distribution at time
#'
#' @param t double time
#'
#' @return distribution function
#'
#' @export
sex_distribution <- function(t) {
  function(x) {
    rep(1/length(x), length(x))
  }
}

#' get n sexes according to sex distribution at time
#'
#' @param t double time
#' @param n integer amount
#'
#' @return vector of sexes
#'
#' @export
get_sexes <- function(t, n) {
  # get distribution function
  distribution_function <- sex_distribution(t)
  # define possible sexes
  sex_range <- c("male", "female")
  # draw sample
  sample(sex_range, size = n, replace = TRUE, prob = distribution_function(sex_range))
}
