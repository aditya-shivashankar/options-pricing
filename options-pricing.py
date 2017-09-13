# -*- coding: utf-8 -*-
"""
Created on Sat Mar 18 09:33:23 2017

@author: ADITYA
"""

import time
import numpy as np
from scipy.stats import norm


def CRR(option, K, T, S0, sigma, r, q, N, exercise):
    time_start = time.clock()
    dt = T/N
    u = np.e**(sigma*np.sqrt(dt))
    d = np.e**(-sigma*np.sqrt(dt))
    a = np.zeros((N + 1, 2))
    option_price = 0
    p_star = (np.e**((r - q)*dt) - d)/(u - d)
    if option == 'C':
        if exercise == 'E':
            for i in range(N+1):
                a[i][0] = S0*(u**(N-i)*(d**i))
                a[i][1] = max(a[i][0] - K, 0)

            for i in range(N):
                for j in range(N - i):
                    a[j][1] = (np.e**(-r*dt))*(p_star*a[j][1] + (1 - p_star)*a[j + 1][1])

        if exercise == 'A':
            for i in range(N+1):
                a[i][0] = S0*(u**(N-i))*(d**i)
                a[i][1] = max(a[i][0] - K, 0)

            for i in range(N):
                for j in range(N-i):
                    a[j][0] = S0*(u**(N-1-i-j))*(d**(j))
                    a[j][1] = max(max(a[j][0] - K, 0), (np.e**(-r * dt))*(p_star*a[j][1] + (1 - p_star)*a[j + 1][1]))

    if option == 'P':
        if exercise == 'E':
            for i in range(N+1):
                a[i][0] = S0*(u**(N-i)*(d**i))
                a[i][1] = max(K - a[i][0], 0)

            for i in range(N):
                for j in range(N - i):
                    a[j][1] = (np.e**(-r*dt))*(p_star*a[j][1] + (1 - p_star)*a[j + 1][1])

        if exercise == 'A':
            for i in range(N+1):
                a[i][0] = S0*(u**(N-i)*(d**i))
                a[i][1] = max(K - a[i][0], 0)

            for i in range(N):
                for j in range(N-i):
                    a[j][0] = S0*(u**(N-1-i-j))*(d**j)
                    a[j][1] = max(max((K - a[j][0]), 0), (np.e**(-r*dt))*(p_star*a[j][1] + (1 - p_star)*a[j + 1][1]))

    option_price = a[0][1]
    run_time = time.clock() - time_start
    return option_price, run_time


def BSM(option, K, T, S0, sigma, r, q):
    d1 = (np.log(S0/K)+(r-q+0.5*(sigma**2))*T)/(sigma*(np.sqrt(T)))
    d2 = d1 - sigma*(np.sqrt(T))
    if option == 'C':
        option_price = S0*(np.e**(-q*T))*(norm.cdf(d1)) - K*(np.e**(-r*T))*(norm.cdf(d2))
    if option == 'P':
        option_price = K*(np.e**(-r*T))*(norm.cdf(-d2)) - S0*(np.e**(-q*T))*(norm.cdf(-d1))

    return option_price
