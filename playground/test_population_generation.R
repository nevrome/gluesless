timeframe <- 0:200

settings <- new(
  "population_settings",
  time =  timeframe,
  population_size_function = population_size,
  unit_amount_function = unit_amount,
  age_distribution_function = age_distribution,
  age_range = 1:100,
  sex_distribution_function = sex_distribution,
  sex_range = c("male", "female"),
  unit_distribution_function = unit_distribution,
  start_unit_vector = 1:10
)

test <- settings %>%
  generate_population()

population_real <- test %>% count_living_humans_over_time(timeframe)

population_expected <- tibble::tibble(
  t = timeframe,
  n = population_size(t)
)

library(ggplot2)
test %>%
  ggplot() +
  geom_segment(
    aes(y = id, yend = id, x = birth_time, xend = death_time, color = unit)
  ) +
  #facet_wrap(~unit) +
  geom_vline(aes(xintercept = timeframe[1])) +
  geom_vline(aes(xintercept = timeframe[length(timeframe)]))


