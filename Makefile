all: fdm.png fdtd.png

main: include/*hpp src/*cpp
	g++ -Wall -fopenmp -march=native -O3 -Iinclude -g -fno-omit-frame-pointer src/*cpp -ffast-math -o main

runmain: main
	$(shell ./main)

fdm.png: runmain
	$(shell python -c 'import numpy as np; from matplotlib import pyplot; aa = np.loadtxt("fdm.dat"); pyplot.imsave("fdm.png", aa)')

fdtd.png: runmain
	$(shell python -c 'import numpy as np; from matplotlib import pyplot; aa = np.loadtxt("fdtd.dat"); aa = aa.reshape(np.sqrt(len(aa)), np.sqrt(len(aa))); pyplot.imsave("fdtd.png", aa)')

clean:
	rm main fdm.{png,dat} fdtd.{png,dat}
