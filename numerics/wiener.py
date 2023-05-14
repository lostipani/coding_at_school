import numpy as np
from matplotlib import pyplot as plt

class Bt:
    def __init__(self, x0, y0):
        self.x0 = x0
        self.y0 = y0

    def simulate1D(self, T, a=1):
        self.x = self._simul(T,a)
        plt.plot(self.time, self.x)
        plt.show()
    
    def simulate2D(self, T, a=1):
        self.x = self._simul(T,a)
        self.y = self._simul(T,a)
        plt.plot(self.x, self.y)
        plt.show()

    def _simul(self, T, a=1):
        rr = np.random.randint(2, size=T)
        tt = np.arange(T)
        yy = [0]
        for k in range(1,T):
            if rr[k]%2 == 0:
                yy.append(yy[-1] - a)
            else:
                yy.append(yy[-1] + a)

        self.time = tt
        return yy
