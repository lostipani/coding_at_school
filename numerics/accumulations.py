"""
Accumulation functions for simple and compound interests. Comparison and some maths around.

1) Compare accumulations by compound or simple interest, for a list of interest rates
2) Compare compound accumul functions with different rate frequency
3) Evaluate Euler constant number as limit
4) Estimate integral of exponential in given domain

5Bsa, LSGalilei, 2022
"""

import matplotlib
from matplotlib import pyplot as plt # module for plotting, plt is a nickname for pyplot
import numpy as np # module for algebra (generate n-dim arrays, math functions, ...)
import math

# ------------------------------------
# Definition of accumulation functions

def simple(mu, t, floor=True):
	return (1 + mu*np.floor(t)) if floor else (1 + mu*t)

def compound(mu, t, floor=True):
	return (1 + mu)**np.floor(t) if floor else (1 + mu)**t


# -------------------------------
# Functions for plotting purposes

def plot_exp(freq: list=[1,2,4,12,52,365], rate: float=0.2, T: float=5, N: int=100) -> 'plot exponential fun estimate':
    """
    Plot compound interest for different fractions of a year (given an interest rate) against exponential function.
    Args:
        freq - fractions of a year, thus 2->semester, 52->week, 365->day
        rate - yearly interest rate
        T    - max time / year
        N    - time steps
    """

    tt = np.linspace(0,T,N) # time axis [0,N) in N steps

    for ff in freq: # plot for each frequency
        plt.plot(tt, compound(rate/ff, ff*tt), label=str(ff))
    plt.plot(tt, np.exp(rate*tt), 'k--') # plot analytical exponential function
    
    plt.legend()
    plt.show()


def plot_accumul(rate: float=0.2, T: float=5, N: int=100) -> 'plot accumulation functions for given rate':
    
    """
    Plot simple and compound interest for given interest rate.
    Args:
        rate - yearly interest rate
        T    - max time / year
        N    - time steps
    """
    
    tt = np.linspace(0,T,N) # time axis [0,N) in N steps

    # plot simple and compound accumulations
    plt.plot(tt, compound(rate, tt), '-', label=r'compound: $\mu = $ {:.2f}'.format(rate))
    plt.plot(tt, simple(rate, tt), '--', label=r'simple: $\mu = $ {:.2f}'.format(rate))

    # cosmetics
    plt.xlabel("time / year")
    plt.ylabel("normalized")
    plt.title("Comparison compound vs simple interest")
    plt.legend()

    plt.show() # force producing the plot in a window
    
def plot_diff_accumul(rate: list=[], T: float=5, N: int=1000) -> 'plot difference between compound and simple accumulation function':
    
    """
    Plot difference between compound and simple accumulations for a list of interest rates.
    
    Args:
        rate - yearly interest rate
        T    - max time / year
        N    - time steps
    """

    # if list is not provided, default range is [0.05,0.95) by 0.05 steps
    if rate == []:
        rate = list(np.arange(0.05,0.95,0.05))

    tt = np.linspace(0,T,N) # time axis [0,N) in N steps

    for mu in rate: # plot diff for each rate
        plt.plot(tt, compound(mu, tt, floor=False) - simple(mu, tt, floor=False), '-', label=r'$\mu = $ {:.2f}'.format(mu))
    plt.plot(tt,np.zeros(tt.shape),'k--') # plot zero line
    
    # cosmetics
    plt.xlabel("time / year")
    plt.ylabel("difference comp-simple")
    plt.title("Comparison compound vs simple interest")
    plt.legend()

    plt.show() # force producing the plot in a window
    

# ------------------
# Integral estimation

def diff2exp(freq: list=[1,2,4,12,52,365], rate: float=0.2, T: float=5, N: int=1000, M: int=1000, seed: int=0, logging: bool=True) -> (dict, dict, dict):
    """
    Evaluate difference between area below compound accumulation at different fractions of a year (given an interest rate) and integral of exponential.
    Monte Carlo and the Trapezoid methods are employed.

    Args:
        freq    - fractions of a year, thus 2->semester, 52->week, 365->day
        rate    - yearly interest rate
        T       - max time / year
        N       - time steps
        M       - Monte Carlo number of markers
        seed    - seed for initializing the PNRG
        logging - to produce verbose output
    """

    tt = np.linspace(0,T,N) # time axis [0,N) in N steps

    exparea = (1/rate)*(np.exp(rate*T) - np.exp(rate*tt[0])) # integral of exp within [0,T]
    
    # plot for each frequency
    est1 = dict()
    est2 = dict()
    est3 = dict()
    for ff in freq:
        area_mc = _montecarlo(compound(rate/ff, ff*tt), tt, M, seed)
        area_tz = np.trapz(compound(rate/ff, ff*tt), tt)
        
        est1[ff] = abs(area_mc[0]-exparea)/exparea
        est2[ff] = abs(area_mc[1]-exparea)/exparea
        est3[ff] = abs(area_tz-exparea)/exparea
        
        if logging: print("Frequency: {:d},\t by MC frequentist: {:.5f} \t by MC average: {:.5f} \t by Trapz: {:.5f}".format(ff, est1[ff], est2[ff], est3[ff]))
    
    return (est1, est2, est3) # return a tuple with the 3 dictionaries


def conv2exp(M: list=[1e3,1e6], N: int=1000, freq: list=[100,500], seed: int=0) -> 'plot of convergence':
    """
    Compare Monte Carlo approaches by analysing convergence to exp integral as a function of number of markers and year fraction (aka frequency).

    Args:
        M       - Monte Carlo number of markers
        N       - number of time steps
        freq    - fractions of a year, thus 2->semester, 52->week, 365->day
        seed    - seed for initializing the PNRG
    """
    
    nmarkers = np.logspace(math.log10(M[0]), math.log10(M[1]))
    yconv    = {"mcFreq": {ff: np.ndarray(nmarkers.shape) for ff in freq}, "mcAvg": {ff: np.ndarray(nmarkers.shape) for ff in freq}}
    
    for m in nmarkers:
        out = diff2exp(freq=freq, N=N, M=int(m), seed=seed, logging=False)
        idx = np.where(nmarkers == m)[0]
        for ff in freq:
            yconv["mcFreq"][ff][idx] = out[0][ff]
            yconv["mcAvg"][ff] [idx] = out[1][ff]
    
    for k in yconv.keys():
        for ff in yconv[k].keys():
            plt.plot(nmarkers, yconv[k][ff], label=k+' for freq='+str(ff))

    plt.plot(nmarkers, np.zeros(nmarkers.shape),'k--')
    plt.legend()
    plt.show()

def _montecarlo(y, x, M: int=1000, seed: int=0, plot: bool=False) -> float :
    """
    Monte Carlo algorithms with unif. distributed PRNs.
    Frequentist approach (Buffon's needle) and average of random rectangles.
    
    Args:
        x, y - co-ordinates of samples
        M    - number of markers
        seed - seed for initializing the PRNG
        plot - boolean to plot markers shot
    
    Return:
        estimated area below sampled curve
    """

    if plot: plt.plot(x, y, 'k-', linewidth=3.)

    # build a box around the curve
    min_y = 0
    if plot: 
        plt.plot([min(x), max(x)], [min_y, min_y], 'k--')
        plt.plot([min(x), max(x)], [max(y), max(y)], 'k--')
        plt.plot([min(x), min(x)], [min_y, max(y)], 'k--')
        plt.plot([max(x), max(x)], [min_y, max(y)], 'k--')
    
    # initialization and generation of PRN
    rng = np.random.default_rng(seed)
    arx = rng.uniform(min(x), max(x), M)
    ary = rng.uniform(min_y, max(y), M)

    # interpolation of curve
    int_y = np.interp(arx, x, y)
    
    # frequentist method
    k = 0
    for j in range(0,M):
        if ary[j] < int_y[j]:
            k = k+1
            if plot: plt.plot(arx[j], ary[j], 'b*')
        else:
            if plot: plt.plot(arx[j], ary[j], 'r*')
    ratio = (max(y)-min_y)*(max(x)-min(x))*k/M
    
    # random sampling average method
    rndavg = int_y.sum()*(max(x)-min(x))/M

    if plot: plt.show()
    return ratio, rndavg



# This is not mandatory. It is used to produce plots by calling the file from terminal as: python3 accumulation.py
if __name__ == "__main__":
    plot_accumul()
    plot_diff_accumul()
    plot_exp()
