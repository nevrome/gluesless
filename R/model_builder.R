#' model_builder class
#'
#' class to store values that should be passed to the model
#'
#' @slot networkland_env string: Description of input graph in graphml format
#' @slot number_iterations integer: Number of model iterations
#' @slot ideas_list test
#' @slot ideas_proportions_matrix test
#'
#' @export
setClass(
  Class = "model_builder",
  slots = c(
    networkland_env = "character",
    number_iterations = "numeric",
    ideas_list = "character",
    ideas_proportions_matrix = "matrix"
  )
)