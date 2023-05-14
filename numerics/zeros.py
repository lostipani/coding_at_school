import numpy as np
import matplotlib.pyplot as plt
from math import sqrt

def import_data(file):
    return np.genfromtxt(file, dtype=float, delimiter='\t')

def f(x, a=1.0, b=0.0, c=-2.0):
    return a*np.power(x,2) + b*x + c

def plot_zero(data, N=1000, **kwargs):
    
    x = np.linspace(data[0][0], data[0][2], N)
    y = f(x)

    plt.plot(x, y, label = r'$y = f(x)$')
    plt.plot([x.min(), x.max()], [0,0], 'k-')
    plt.plot([x.min(), x.min()], [y.min(), y.max()], 'k-')

    for k in range(0,data.shape[0]):
        plt.plot(dat[k,1], 0,'ro')
        plt.annotate(str(k), (dat[k,1],0))

    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()

    if kwargs['xmin'] == []:
        kwargs['xmin'] = x.min()
    if kwargs['xmax'] == []:
        kwargs['xmax'] = x.max()
    plt.axis([kwargs['xmin'], kwargs['xmax'], f(kwargs['xmin']), f(kwargs['xmax'])])

    plt.show()


if __name__ == '__main__':
    plot_zero(import_data('dump.dat'))
