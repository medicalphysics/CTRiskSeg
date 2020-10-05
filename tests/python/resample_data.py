# -*- coding: utf-8 -*-
"""
Created on Tue Sep 29 09:53:49 2020

@author: erlend
"""

import numpy as np
from matplotlib import pylab as plt

def make_array():
    shape = (512, 512)
    ind = np.indices(shape)
    radius = 200
    center = list([sh / 2 for sh in shape])
    circle = sum([(i - c)**2 for i, c in zip(ind, center)]) <= radius**2
    circle.astype(np.double).tofile('circle_in.bin')
    
def read_array():
    in_shape = (512, 512)
    out_shape = (256, 256)
    
    in_arr = np.fromfile('circle_in.bin', dtype=np.double).reshape(in_shape)
    out_arr = np.fromfile('circle_out.bin', dtype=np.double).reshape(out_shape)
    plt.subplot(1, 2, 1)
    plt.imshow(in_arr)
    plt.subplot(1, 2, 2)
    plt.imshow(out_arr)
    plt.show()
    

if __name__=='__main__':
    make_array()
    read_array()