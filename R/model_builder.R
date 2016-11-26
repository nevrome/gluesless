#' modell_builder class
#'
#' test
#'
#' @export
setClass(
  Class = "modell_builder",
  slots = c(
    pop_size = "numeric",
    pop_birthrate = "numeric",
    pop_deathrate = "numeric",
    pop_develop_udef_decision = "logical",
    pop_develop_udef = "function"
  )
)