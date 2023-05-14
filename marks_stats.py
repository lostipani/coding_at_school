import numpy  as np
import pandas as pd
from math              import ceil
from matplotlib        import pyplot as plt
from matplotlib.ticker import MaxNLocator

class classe:
    """
    One instance of CLASSE for each classroom.
    
    Initialize instance with a .xlsx file whose columns are marks for each student. 
    One column per test. The name of the column (first row) is employed as name of the column dataframe. Therefore the time axis is through the columns.
    E.g.:
    Trimestre1  |  Trimestre2  | ....
    8           |  7.5         |
    9           |  10          |
    5.5         |  6           |
    
    The same applies to poll results, where column name is the poll question.
    E.g.
    How do you like me?  |  Is the prof. good?
    5                    |  4  
    1                    |  5
    2                    |  5
    
    
    
    Member functions
    ----------------
    descr : plot of mean and std deviation of marks for each test
    hist  : histograms of marks for each test
    poll  : results of histogram
    """

    def __init__(self, name, url, url_poll=None):
	"""
	Class initializer.
	
	Args
	----
	name     : class name, e.g. "1Xsa"
	url      : file path to .xlsx of marks
	url_poll : file path to .xlsx with results of student poll
	"""
        self.name = name

        try:
            self.df = pd.read_excel(url)
            self.anonymity = self._reshuffle()
            self._df2np()
        except:
            self.df = None
            print("No grade df created")

        try:
            self.df_poll = pd.read_excel(url_poll)
        except:
            self.df_poll = None
            print("No poll df created")

        
    def _reshuffle(self):
        """
        Reshuffle rows for the sake of anonymity.
        """
        self.df = self.df.sample(frac=1).reset_index(drop=True)
        return True

    def _df2np(self):
        """
        Cast dataframe to ndarray.
        """
        self.tab = self.df.to_numpy()


    def descr(self, norm=True, save=False, figsize=(7,3.5)):
        """
        Eval mean and std/mean and plot.

        Args
        ----
        norm    : True for normalized std. dev. on mean
        save    : True for saving figure as self.name+"_descr.png"
        figsize : figure size
        """

        df      = self.df
        assert df is not None, "dataframe not present"
        
        mu      = list()
        sigma   = []
        n_sigma = []
        for cc in df.columns:
            mu.append(df[cc].mean())
            n_sigma.append(df[cc].std()/df[cc].mean())
            sigma.append(df[cc].std())

        fig, axs = plt.subplots(1,2, figsize=figsize)
        axs[0].plot(mu,'b*-', label='mean')
        if norm: 
            axs[1].plot(n_sigma,'ro-', label='std')
            axs[1].set_title('std deviation / media voti')
        else:
            axs[1].plot(sigma,'ro-', label='std')
            axs[1].set_title('std deviation')
        axs[0].set_title('media voti')
        for k in range(2):
            axs[k].set_xticks(range(len(mu)))
            axs[k].set_xticklabels(list(df.columns))

        plt.tight_layout()
        plt.savefig(self.name+"_descr.png")
        plt.show()


    def hist(self, oneplot=False, save=False, bins=range(3,11), figsize=(10,8)):
        """
        Histograms of each test.

        Args
        ----
        oneplot : True for plotting histograms in one axes frame, by using alpha
        save    : True for saving figure as self.name + "_hist.png"
        bins    : int or sequence
        figsize : figure size
        """
        
        df = self.df
        assert df is not None, "dataframe not present"

        if oneplot:
            fig, ax = plt.subplots()
            for cc in df.columns:
                ax.hist(df[cc], bins=bins, alpha=0.5, label=cc, rwidth=0.7, figsize=figsize)
            ax.set_xlabel('voto verifica')
            plt.legend()
            plt.show()
        else:
            hst = df.hist(bins=bins, rwidth=0.7, figsize=figsize)
            
            for k in range(0,len(df.columns),1):
                if k%2==0: hst.ravel()[k].set_ylabel("N. di alunni") ## ylabel only on left margin
                hst.ravel()[k].yaxis.set_major_locator(MaxNLocator(integer=True)) ## force integer yticklabels
            hst.ravel()[len(df.columns)-1].set_xlabel("voto verifica") ## xlabel only at bottom plots
            hst.ravel()[len(df.columns)-2].set_xlabel("voto verifica")
            
            plt.xticks(bins,bins)
            plt.tight_layout()
            
            plt.savefig(self.name+"_hist.png")
            plt.show()
            
            
    def poll(self, save=False, figsize=(20,15)):
        """
        Histograms of poll.

        Args
        ----
        save    : True for saving figure as self.name + "_hist.png"
        figsize : figure size
        """
        
        df = self.df_poll
        assert df is not None, "poll dataframe not present"
        
        cols = df.columns
        half_cols = ceil(len(cols)/2)
        bins = np.arange(1,6.5) - 0.5

        fig, axs = plt.subplots(half_cols, 2, figsize=figsize, dpi=60)
        for k in range(0, len(cols)):
            axs.ravel()[k].hist(df[cols[k]], bins=bins, rwidth=0.5)
            axs.ravel()[k].set_title(cols[k], fontsize=15)
            axs.ravel()[k].grid()
            axs.ravel()[k].yaxis.set_major_locator(MaxNLocator(integer=True)) ## force integer yticklabels
        if len(cols)%2==1: axs.ravel()[-1].remove()
        plt.xlim([0,5.5])
        plt.tight_layout()
        
        plt.savefig(self.name+"_poll.png")
        plt.show()
