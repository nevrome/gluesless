# General roxygen tags
#' @useDynLib gluesless
#' @import Rcpp methods

#' @export
.onUnload <- function (libpath) {
  library.dynam.unload("gluesless", libpath)
}

# load modules
loadModule("Networkland_module", TRUE)
loadModule("Idea_module", TRUE)
