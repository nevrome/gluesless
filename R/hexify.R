#' test
#'
#' test
#'
#' @param area test
#' @param hexproj test
#' @param bufferwidth test
#' @param hexcellsize test
#'
#' @return test
#'
#' @export
hexify <- function(
  area,
  hexproj,
  bufferwidth,
  hexcellsize
) {

  inCRS <- rgdal::CRSargs(area@proj4string)

  area %<>%
    sp::spTransform(
      sp::CRS(hexproj)
    )

  rgeos::gBuffer(
    area,
    width = bufferwidth
  ) %>% sp::spsample(
    type = "hexagonal",
    cellsize = hexcellsize
  ) %>%
    sp::HexPoints2SpatialPolygons(
    ) -> research_area_hex

  #plot(research_area)
  #plot(research_area_hex, add=TRUE)

  research_area_hex %<>%
    sp::spTransform(
      sp::CRS(inCRS)
    )

  return(research_area_hex)
}