population_size <- function(t) {
  (cos(0.1 * t) + 2) * 50
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

# timesteps <- tibble::tibble(
#   t = 1:2000,
#   population_size = population_size(t),
#   population_age_distribution = I(list(population_age_distribution(t)))
# )

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
      birth_time = t - current_age,
      death_time = t + (death_age - current_age),
      sex = population_sex_distribution(t)(number),
      unit = population_unit_distribution(t)(number, 3)
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

time <- 1:200

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

hist(humans$current_age[!humans$dead])

humans %<>% dplyr::select(
  -current_age, -dead
)

humans -> x

heavy_sexing <- function(x) {
  from <- c()
  to <- c()
  label <- c()

  pb <- txtProgressBar(style = 3)
  for (child in 1:nrow(x)) {
    potential_parents <- x %>% dplyr::filter(
      (birth_time + 12) <= x$birth_time[child],
      x$birth_time[child] <= (birth_time + 60),
      unit == x$unit[child]
    )
    if (!all(c("male", "female") %in% unique(potential_parents$sex))) {next}
    mother <- potential_parents %>%
      dplyr::filter(sex == "female") %>%
      dplyr::sample_n(1) %$%
      id
    father <- potential_parents %>%
      dplyr::filter(sex == "male") %>%
      dplyr::sample_n(1) %$%
      id
    from <- append(from, c(mother, mother, father))
    to <- append(to, c(father, child, child))
    label <- append(label, c("❤", "✌", "✌"))

    setTxtProgressBar(pb, child/nrow(x))
  }
  close(pb)

  tibble::tibble(from, to, label)
}

humans %>% heavy_sexing() -> hu

# hu %>%
#  igraph::graph_from_data_frame(d = ., directed = FALSE)  %>%
#   visNetwork::visIgraph(layout = "layout_in_circle")

humans_sorted <- humans %>%
  dplyr::arrange(
    unit, id
  )

library(ggplot2)
humans %>%
  ggplot() +
  geom_segment(
    aes(y = id, yend = id, x = birth_time, xend = death_time, color = sex)
  ) +
  facet_wrap(~unit) +
  geom_vline(aes(xintercept = time[1])) +
  geom_vline(aes(xintercept = time[length(time)])) +
  geom_line(
    data = spu,
    aes(x = t, y = n - max(spu$n) - 50),
    color = "black"
  ) +
  geom_line(
    data = hu,
    aes(x = t, y = n - max(spu$n) - 50),
    color = "red"
  )


hu <- tibble::tibble(t = time) %>%
  dplyr::mutate(
    n = t %>% purrr::map_int(
      function(x) {
        humans %>% dplyr::filter(
          birth_time <= x & x <= death_time
        ) %>%
          nrow() %>%
          return()
      }
    )
  )

spu <- tibble::tibble(
  t = time,
  n = population_size(t)
)


