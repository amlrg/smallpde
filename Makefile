all: fdm.mp4 fdtd.mp4

main: include/*hpp src/*cpp
	g++ -Wall -fopenmp -march=native -O3 -Iinclude -g -fno-omit-frame-pointer src/*cpp -ffast-math -o main

runmain: main
	$(shell ./main)

fdm.mp4: runmain util/genvideo.py
	$(shell python util/genvideo.py fdm.dat fdm.mp4)

fdtd.mp4: runmain util/genvideo.py
	$(shell python util/genvideo.py fdtd.dat fdtd.mp4)

clean:
	rm main fdm.{mp4,dat} fdtd.{mp4,dat}
