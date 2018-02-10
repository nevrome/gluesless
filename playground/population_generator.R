population_size <- function(t) {
  (cos(0.1 * t) + 2) * 500
}

population_age_distribution <- function(t) {
  function(n) {
    as.integer(abs(rnorm(n, 0, sd = 30)))
  }
}

population_sex_distribution <- function(t) {
  function(n) {
    sample(c("male", "female"), n, replace = TRUE)
  }
}

population_unit_distribution <- function(t) {
  function(n, amount_units) {
    sample(1:amount_units, n, replace = TRUE)
  }
}

timesteps <- tibble::tibble(
  t = 1:2000,
  population_size = population_size(t),
  population_age_distribution = I(list(population_age_distribution(t)))
)

population_age_distribution(10)(10)

generate_humans <- function(t, start_id, number, start_age = NA) {
  if (number > 0) {
    tibble::tibble(
      id = start_id:(start_id + number - 1),
      death_age = population_age_distribution(t)(number),
      current_age = if (is.na(start_age)) {
          as.integer(runif(number, min = 0, max = death_age))
        } else {
          as.integer(start_age)
      },
      dead = FALSE,
      birth_time = t,
      death_time = t + death_age,
      sex = population_sex_distribution(t)(number),
      unit = population_unit_distribution(t)(number, 40)
    ) %>% return()
  } else {
    tibble::tibble(
      id = integer(),
      death_age = integer(),
      current_age = integer(),
      dead = logical(),
      birth_time = integer(),
      death_time =  integer(),
      sex = character(),
      unit = integer()
    )
  }
}

time <- 1:500

humans <- generate_humans(0, 1, population_size(0))

for (t in time) {
  humans[!humans$dead, ] %<>%
    dplyr::mutate(
      current_age = as.integer(current_age + 1),
      dead = current_age >= death_age
    )

  alive <- nrow(humans[!humans$dead, ])
  # deaths <- sum(humans$death_time == t, na.rm = TRUE)

  if (alive >= population_size(t)) {
    births <- 0
  } else {
    births <- population_size(t) - alive
  }

  humans %<>% rbind(
    generate_humans(t, max(humans$id + 1), births, 0)
  )

}

hu <- tibble::tibble(t = time) %>%
  dplyr::mutate(
    n = purrr::map_int(
      t, function(x) {
        humans %>% dplyr::filter(
          birth_time <= x & x <= death_time
        ) %>%
          nrow() %>%
          return()
      }
    )
  )


plot(time, population_size(time))
points(hu$t, hu$n, col = "red")

hist(humans$current_age[!humans$dead])
