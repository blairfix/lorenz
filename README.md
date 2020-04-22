# lorenz

`lorenz` is an R function to generate a Lorenz curve from a raw distribution of income. It is implemented in [RcppArmadillo](https://cran.r-project.org/web/packages/RcppArmadillo/index.html).


### Inputs

* `pay` = a vector of raw income values
* `n_bins` =  the number of desired points on the Lorenz curve

### Output
`lorenz` outputs a two-column matrix. Column 1 contains income percentiles. Column 2 contains the cumulative share of income.

### Example:

```R
library(RcppArmadillo)
library(Rcpp)

sourceCpp("lorenz.cpp")

pay = rlnorm(10^7, 1, 1)

lorenz(pay, n_bins = 100)

```

Returns a matrix with income percentiles in `[,1]` and cumulative share of income in `[,2]`.

```R
          [,1]         [,2]
 [1,] 0.000001 2.370526e-09
 [2,] 0.000006 3.331201e-08
 [3,] 0.000531 9.516957e-06
 [4,] 0.016166 8.400633e-04
 [5,] 0.156552 2.230175e-02
 [6,] 0.550062 1.912067e-01
 [7,] 0.896353 6.034795e-01
 [8,] 0.991704 9.192820e-01
 [9,] 0.999807 9.948190e-01
[10,] 1.000000 1.000000e+00
```


### Installation
To use `lorenz`, install the following R packages:
 * [Rcpp](https://cran.r-project.org/web/packages/Rcpp/index.html) 
 * [RcppArmadillo](https://cran.r-project.org/web/packages/RcppArmadillo/index.html) 

Put the source code (`lorenz.cpp`) in the directory of your R script. Then source it with the command `sourceCpp(lorenz.cpp)`.


### Performance

The `lorenz` function calculates a limited number of points on the Lorenz curve.  Because it uses logarithmic spacing, these limited points are still sensitive to top incomes.

The main advantage of using a limited number of points is plotting speed. Plotting a Lorenz curve with several million points is slow. Plotting the same curve with a hundred points is fast. 

For big datasets, `lorenz` is about 10 times faster than the similar `Lc` function in the [ineq](https://cran.r-project.org/web/packages/ineq/ineq.pdf) package:


```R
library(RcppArmadillo)
library(Rcpp)
library(ineq)
library(microbenchmark)

sourceCpp("lorenz.cpp")

pay = rlnorm(10^7, 1, 1)

microbenchmark(
  lorenz_cpp =   plot(lorenz(pay, 100)),
  times = 5
)

microbenchmark(
  Lc_ineq = plot(Lc(pay)),
  times = 5
)

```

Returns the following:

```R
Unit: seconds
       expr      min       lq     mean   median       uq     max neval
 lorenz_cpp 1.280979 1.302514 1.310443 1.308688 1.311864 1.34817     5

Unit: seconds
    expr      min       lq     mean   median       uq      max neval
 Lc_ineq 1.878216 16.79187 14.11446 17.06061 17.34391 17.49771     5
```




