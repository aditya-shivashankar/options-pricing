# options-pricing
Options pricing implementation in C++ and Python
The CRR Binomial model has been implemented for European and American calls and puts in the required format:

Binomial (Option, K, T, S0,sigma, r, q, N, Exercise )

Where the symbols stand for the usual quantities. The output is the price of the option as well
as the runtime.
Option-'C' or 'P'
K-Strike
T- time to maturity in months
sigma-volatility
r, q -rates
N-number of steps
Exercise-'A' or 'E'

European Option

First an array is created with length N+1. Then each element is initialized to the payoffs at
maturity. The values of u and d are calculated from sigma. Using this we find the value of expected payoff for previous step which is updated in the array. Continuing in this way we find the value at t=0 which is the price of option.


American Option

Two arrays of length N+1 are created. One array is initialized to the payoffs at maturity and the
other is initialized to the stock price at maturity. At every iteration, payoff as well as stock price
is updated in the arrays. Continuing in this way we finally get value of option at t=0 which is the
price of the option
