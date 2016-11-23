# General roxygen tags
#' @useDynLib gluesless
#' @import Rcpp

#' @export
.onUnload <- function (libpath) {
  library.dynam.unload("gluesless", libpath)
}

# load modules
loadModule("Population_module", TRUE)
