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

actors <- data.frame(name=c("Alice", "Bob", "Cecil", "David",
                            "Esmeralda"),
                     age=c(48,33,45,34,21),
                     gender=c("F","M","F","M","F"))
relations <- data.frame(from=c("Bob", "Cecil", "Cecil", "David",
                               "David", "Esmeralda"),
                        to=c("Alice", "Bob", "Alice", "Alice", "Bob", "Alice"),
                        #same.dept=c(FALSE,FALSE,TRUE,FALSE,FALSE,TRUE),
                        friendship=c(4,5,5,2,1,1), advice=c(4,5,5,4,2,3))
g <- graph_from_data_frame(relations, directed=FALSE, vertices=actors)

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
  networkland_env = hununu
)

run(test_builder) -> fluut

fluut %>% graphread() -> h

summary(g)
summary(h)
plot(g)
plot(h)

#####


