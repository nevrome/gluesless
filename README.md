[![Build Status](https://travis-ci.com/nevrome/gluesless.svg?token=vxsQ9RjxoGASGtX4Q8jc&branch=master)](https://travis-ci.com/nevrome/gluesless)
[![codecov](https://codecov.io/gh/nevrome/gluesless/branch/master/graph/badge.svg?token=CzPxma1Ac3)](https://codecov.io/gh/nevrome/gluesless)

## Overview

gluesless is the implementation of a diffusion of innovation model.

## Usage example

```{r}
library(igraph)
library(magrittr)
library(gluesless)
library(tidyverse)
library(ggraph)

nodes <- data.frame(
  name = seq(0, 19, by = 1),
  x = runif(20, 0, 100) %>% round(0),
  y = runif(20, 0, 100) %>% round(0)
)

edges <- data.frame(
  from = sample(nodes$name, 30, replace = TRUE),
  to = sample(nodes$name, 30, replace = TRUE),
  distance = runif(30, 0, 100) %>% round(0)
  )

g <- graph_from_data_frame(
  edges,
  directed = FALSE,
  vertices = nodes
  ) %>%
  igraph::simplify(
    edge.attr.comb = "mean"
  )

g <- set.graph.attribute(g, "graph_name", "testgraph")

#plot(g)

new(
  "modell_builder",
  networkland_env = graphwrite(g),
  number_iterations = 40
) %>%
  run() %$%
  idea_exp -> runres

plot_devel(g, runres, store = FALSE)
```