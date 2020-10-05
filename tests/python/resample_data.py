# -*- coding: utf-8 -*-
"""
Created on Tue Sep 29 09:53:49 2020

@author: erlend
"""

import numpy as np


def make_array():
    shape = (512, 512)
    ind = np.indices(shape)
    radius = 200
    center = list([sh / 2 for sh in shape])
    circle = sum([(i - c)**2 for i, c in zip(ind, center)]) <= radius**2
    circle.astype(np.double).tofile('circle_in.bin')
    
 

if __name__=='__main__':
    make_array()