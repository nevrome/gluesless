#' add input graph vertex coordinates to model results
#'
#' @param idea_exp igraph graph object
#' @param world_graph igraph graph object
#'
#' @return data.frame
#'
#' @export
link_ideas_world <- function(idea_exp, world_graph) {

  # check if runres is empty
  if (nrow(idea_exp) == 0) {
    return(NULL)
  }

  # get nodes from graph
  nodes <- igraph::get.vertex.attribute(world_graph) %>%
    as.data.frame(stringsAsFactors = FALSE)

  # split idea_exp into list by timestep
  timelist <- plyr::dlply(idea_exp, "timestep", identity)

  # add nodes coordinates to individual idea positions
  # by joining nodes and idea_exp
  states <- timelist %>% purrr::map(
    function(x) {
      dplyr::inner_join(nodes, x, by = "region_name") %>%
        dplyr::group_by_("idea") %>%
        as.data.frame()
    }
  )

  return(states)
}