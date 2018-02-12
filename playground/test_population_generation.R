settings <- new(
  "population_settings",
  time = 1:200,
  population_size_function = population_size,
  unit_amount_function = unit_amount,
  age_distribution_function = age_distribution,
  age_range = 1:100,
  sex_distribution_function = sex_distribution,
  sex_range = c("male", "female"),
  unit_distribution_function = unit_distribution,
  start_unit_vector = 1:10
)

settings %>%
  generate_population()
