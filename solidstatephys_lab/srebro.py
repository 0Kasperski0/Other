# -*- coding: utf-8 -*- 
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import MaxNLocator
import numpy as np
import math as m
import seaborn as sns; #sns.set()
import pandas as pd 
import sys
from datetime import datetime
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)

file='srbr.txt'
data=np.loadtxt(file,usecols=np.arange(0,2))
y=data[:,1]
x=data[:,0]
fig,ax=plt.subplots()
ax.plot(x,y,'b',linewidth=0.75)
ax.xaxis.set_major_locator(MultipleLocator(2.5))
ax.xaxis.set_major_formatter(FormatStrFormatter('%1.1f'))
ax.xaxis.set_minor_locator(MultipleLocator(0.5))

ax.yaxis.set_major_locator(MultipleLocator(4))
ax.yaxis.set_major_formatter(FormatStrFormatter('%d'))
ax.yaxis.set_minor_locator(MultipleLocator(1))
ax.set_ylim(ymin=0)
ax.set_xlim(xmin=0)
ax.grid(b=True, which='major', color='k', linestyle='--',alpha=0.3)


ax.fill_between(x,y, where=(x>15.4)&(x<16.1),interpolate=True,color='red',alpha=0.3)
ax.text(15.8, 14, r'ZrK$\alpha$', fontsize=10,rotation=90)

ax.fill_between(x,y, where=(x>17.1)&(x<17.9),interpolate=True,color='blue',alpha=0.3)
ax.text(18, 44, r'ZrK$\beta$', fontsize=10,rotation=90)

ax.fill_between(x,y, where=(x>20.7)&(x<21.6),interpolate=True,color='green',alpha=0.3)
ax.text(21.2, 22, r'PbK$\alpha$', fontsize=10,rotation=90)

ax.fill_between(x,y, where=(x>24.7)&(x<25.5),interpolate=True,color='yellow',alpha=0.3)
ax.text(22, 35, r'AgK$\alpha$', fontsize=10,rotation=90)

ax.fill_between(x,y, where=(x>31.7)&(x<32.5),interpolate=True,color='pink',alpha=0.3)
ax.text(24.8, 15.5, r'AgK$\beta$', fontsize=10,rotation=90)
ax.text(25.4, 17.5, r'SnK$\alpha$', fontsize=10,rotation=90)

ax.fill_between(x,y, where=(x>21.7)&(x<22.5),interpolate=True,color='fuchsia',alpha=0.3)
ax.text(32, 10, r'BaK$\alpha$', fontsize=10,rotation=90)

#ax.fill_between(x,y, where=(x>23.6)&(x<23.8),interpolate=True,color='magenta',alpha=0.3)
#ax.fill_between(x,y, where=(x>28.4)&(x<28.5),interpolate=True,color='magenta',alpha=0.3)




plt.xlabel('Energia [keV]')
plt.ylabel('Zliczenia [cps]')

fig.set_size_inches(12.8,7.2)

plt.savefig("ayya.png", bbox_inches = 'tight',
    pad_inches = 0)

plt.show()