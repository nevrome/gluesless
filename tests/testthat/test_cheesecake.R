context("Tests of function cheesecake")

res <- cheesecake()

test_that(
  "the output of pnp is a boolean value",  {
    expect_true(
      is.logical(res)
    )
  }
)
