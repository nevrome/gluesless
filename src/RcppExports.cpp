// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// cheesecake
bool cheesecake(int i);
RcppExport SEXP gluesless_cheesecake(SEXP iSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type i(iSEXP);
    rcpp_result_gen = Rcpp::wrap(cheesecake(i));
    return rcpp_result_gen;
END_RCPP
}
// graphtest
std::string graphtest();
RcppExport SEXP gluesless_graphtest() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(graphtest());
    return rcpp_result_gen;
END_RCPP
}
// run
SEXP run(SEXP modell_builder);
RcppExport SEXP gluesless_run(SEXP modell_builderSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type modell_builder(modell_builderSEXP);
    rcpp_result_gen = Rcpp::wrap(run(modell_builder));
    return rcpp_result_gen;
END_RCPP
}
