# General roxygen tags
#' @useDynLib gluesless
#' @importFrom Rcpp sourceCpp

#' @export
.onUnload <- function (libpath) {
  library.dynam.unload("gluesless", libpath)
}