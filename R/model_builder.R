#' model_builder class
#'
#' class to store values that should be passed to the model
#'
#' @slot networkland_env string: Description of input graph in graphml format
#' @slot number_iterations integer: Number of model iterations
#' @slot initial_idea_starting_positions numeric vector: ids of nodes where the initial idea starts
#'
#' @export
setClass(
  Class = "model_builder",
  slots = c(
    networkland_env = "character",
    number_iterations = "numeric"
  )
)