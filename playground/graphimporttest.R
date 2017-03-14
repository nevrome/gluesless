library(igraph)

test <- graphtest()

graphtrans <- function(inputstring, format = "graphml"){
  charToRaw(inputstring) %>%
    rawConnection() %>%
    igraph::read_graph(., format = format) %>%
    return()
}

graphtrans(test) %>%
  plot()
