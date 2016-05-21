#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys

fig = plt.figure()

data = np.loadtxt(sys.argv[1])
dmin = data.flatten().min()
dmax = data.flatten().max()
ims = []
for i in range(100):
    im = plt.imshow(data[np.size(data, 1)*i:np.size(data, 1)*(i+1), :], vmin=dmin, vmax=dmax, cmap='viridis', animated=True)
    ims.append([im])

ani = animation.ArtistAnimation(fig, ims, interval=50, blit=True,
                                repeat_delay=1000)

ani.save(sys.argv[2])
