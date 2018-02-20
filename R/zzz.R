# General roxygen tags
#' @useDynLib gluesless
#' @import Rcpp methods
#' @import RcppProgress
#' @importFrom rlang .data
#' @importFrom magrittr "%>%"
#' @importFrom magrittr "%<>%"
#' @importFrom magrittr "%$%"

#' @export
.onUnload <- function (libpath) {
  library.dynam.unload("gluesless", libpath)
}

# defining global variables
# ugly solution to avoid magrittr NOTE
# see http://stackoverflow.com/questions/9439256/how-can-i-handle-r-cmd-check-no-visible-binding-for-global-variable-notes-when
globalVariables(".")