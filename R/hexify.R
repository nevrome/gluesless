#' test
#'
#' test
#'
#' @param areapath test
#' @param clippath test
#' @param hexproj test
#' @param bufferwidth test
#' @param hexcellsize test
#'
#' @return test
#'
#' @export
hexify <- function(
  areapath,
  clippath,
  hexproj,
  bufferwidth,
  hexcellsize
) {

  area <- rgdal::readOGR(
    dsn = areapath
  )

  inCRS <- rgdal::CRSargs(area@proj4string)

  research_area_border <- rgdal::readOGR(
    dsn = clippath
  )

  research_area <- rgeos::gIntersection(
    area, research_area_border, byid = TRUE,
    drop_lower_td = TRUE
  ) %>%
    sp::spTransform(
      sp::CRS(hexproj)
    )

  rgeos::gBuffer(
    research_area,
    width = bufferwidth
  ) %>% sp::spsample(
    type = "hexagonal",
    cellsize = hexcellsize
  ) %>%
    sp::HexPoints2SpatialPolygons(
    ) -> research_area_hex

  #plot(research_area)
  #plot(research_area_hex, add=TRUE)

  research_area_hex %>%
    sp::spTransform(
      sp::CRS(inCRS)
    ) -> research_area_hex_re

  rsa_hex_df <- ggplot2::fortify(research_area_hex_re, region = "id")

  return(rsa_hex_df)
}