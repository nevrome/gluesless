test <- graphtest()

library(sna)
gra <- read.dot(textConnection(test))

library(igraph)
gra2 <- graph_from_adjacency_matrix(gra)

plot(gra2)
