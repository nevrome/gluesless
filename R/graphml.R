#' test
#'
#' test
#'
#' @param inputstring test
#' @param format test
#'
#' @return test
#'
#' @importFrom magrittr "%>%"
#'
#' @export
graphread <- function(inputstring, format = "graphml"){
  inputstring %>%
    charToRaw() %>%
    rawConnection() %>%
    igraph::read_graph(., format = format) %>%
    return()
}

#' test
#'
#' test
#'
#' @param igraphobj test
#' @param format test
#'
#' @return test
#'
#' @export
graphwrite <- function(igraphobj, format = "graphml"){
  rawConnection(raw(0), "r+") -> zz
  igraph::write_graph(igraphobj, file = zz, format = format)
  rawConnectionValue(zz) %>%
    rawToChar() -> res
  close.connection(zz)
  res %>% return()
}