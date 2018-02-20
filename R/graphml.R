#' string->igraph
#'
#' create igraph object from string
#'
#' @param inputstring string that describes a graph
#' @param format format of the string
#'
#' @return igraph object
#'
#' @export
graphread <- function(inputstring, format = "graphml"){
  inputstring %>%
    charToRaw() %>%
    rawConnection() %>%
    igraph::read_graph(., format = format) %>%
    return()
}

#' igraph->string
#'
#' create string from igraph object
#'
#' @param igraphobj igraph object
#' @param format format of the string
#'
#' @return string
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