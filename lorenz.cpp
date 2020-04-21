#include <RcppArmadillo.h>

// This function generates a Lorenz curve from the vector 'pay'.
// Lorenz curve values are calculated for a logarithmically spaced vector over the data range
// with 'n_bins' indicating the number of points.

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::export]]


arma::mat lorenz(   arma::vec pay,
                    int n_bins
                )
{

    int n_people = pay.size();
    double lower = pay.min();
    double upper = pay.max();

    arma::vec bin_vec = arma::logspace( std::log10(lower), std::log10(upper), n_bins);

    // get lorenz
    arma::mat result(n_bins, 2);

    int n = bin_vec.size();
    double total_income = arma::sum(pay);

    for(int i = 0; i < n; ++i){

        int person_counter = 0;
        double pay_counter = 0;
        double bin = bin_vec[i];

        for(int j = 0; j < n_people; j++){

            if(pay[j] <= bin){
                ++person_counter;
                pay_counter = pay_counter + pay[j];
            }
        }

        result(i, 0) = (double) person_counter/ (double) n_people;
        result(i, 1) = pay_counter / total_income;
    }


    return result;

}
