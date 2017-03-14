library(igraph)
library(magrittr)

test <- graphtest()

graphread <- function(inputstring, format = "graphml"){
  inputstring %>%
    charToRaw() %>%
    rawConnection() %>%
    igraph::read_graph(., format = format) %>%
    return()
}

graphread(test) %>%
  plot()

#####

library(igraph)
library(magrittr)

g <- sample_pa(100)

graphwrite <- function(igraphobj, format = "graphml"){
  rawConnection(raw(0), "r+") -> zz
  write_graph(igraphobj, file = zz, format = format)
  rawConnectionValue(zz) %>%
    rawToChar() %>%
    return()
}

hununu <- graphwrite(g)

#####

test_builder <- new(
  "modell_builder",
  population_size = 20,
  networkland_env = hununu
)

run(test_builder) -> fluut

fluut %>% graphread() %>% plot()