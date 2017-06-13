#' @export
link_ideas_world <- function(idea_exp, world_graph) {

  # check if runres is empty
  if (nrow(idea_exp) == 0) {
    return(NULL)
  }

  # get vertices from graph
  vertices <- igraph::get.vertex.attribute(world_graph) %>%
    as.data.frame(stringsAsFactors = FALSE) %>%
    dplyr::mutate_("name" = ~as.numeric(name))

  # split idea_exp into list by timestep
  timelist <- plyr::dlply(idea_exp, "timestep", identity)

  # add vertices coordinates to individual idea positions
  # by joining vertices and idea_exp
  states <- timelist %>% purrr::map(
    function(x) {
      dplyr::inner_join(vertices, x, by = c("name" = "vertices")) %>%
        dplyr::group_by_("ideas") %>%
        dplyr::mutate_("n" = ~n()) %>%
        as.data.frame()
    }
  )

  return(states)
}