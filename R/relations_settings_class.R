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
    population = "data.frame"
  )
)
