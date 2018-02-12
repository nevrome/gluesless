#' generate population
#'
#' @param settings
#'
#' @return huup
#'
#' @export
generate_population <- function(settings) {

  initial_population <- generate_humans(
    t = 0,
    n = settings@population_size_function(0),
    start_id = 1,
    start_age = NA,
    settings = settings,
    unit_vector = settings@start_unit_vector
  )

  final_population <- initial_population %>% simulate_growth(
    time = settings@time,
    settings = settings
  )

  return(final_population)

}