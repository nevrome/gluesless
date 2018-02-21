#' relations_settings class
#'
#' class to store values that should be passed to the relations generator
#'
#' @slot population test
#'
#' @export
setClass(
  Class = "relations_settings",
  slots = c(
    population = "data.frame",
    monogamy_probability = "numeric",
    start_fertility_age = "numeric",
    stop_fertility_age = "numeric",
    same_unit_as_child_probability = "numeric",
    same_unit_as_partner_probability = "numeric"
  )
)
