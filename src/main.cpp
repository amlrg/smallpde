#include "types.hpp"
#include "fdm.hpp"
#include "fdtd.hpp"
#include <fstream>

void fdm_test() {
  // set up params
  Params<ProblemType::Diffusion> p;
  p.N  = 256;
  p.timeSteps = 1024;
  p.D = 1.;
  p.dx = 1./(p.N-1);
  p.dt = p.dx*p.dx/4 / 2; // stable/2  for explicit Euler
  Field f(p.N*p.N);

  std::ofstream out("fdm.dat", std::ofstream::out);
  for (int t = 0; t < 100; ++t) {
    // calc
    f = fdm(f, p);

    // print
    for (int i = 0; i < p.N; ++i) {
      for (int j = 0; j < p.N; ++j)
	out << f[p.N * i + j] << " ";
      out << std::endl;
    }
  }
}

void fdtd_test() {
  // set up params
  Params<ProblemType::Maxwell> p;
  p.N  = 64;
  p.timeSteps = 50;
  p.dx = 1./(p.N-1);
  p.dt = 0.0001;
  Field fE(3*p.N*p.N*p.N);
  Field fH(3*p.N*p.N*p.N);


  std::ofstream out("fdtd.dat", std::ofstream::out);
  const int DIM = 0;
  const int i   = p.N/2;

  for (int t = 0; t < 100; ++t) {
    // calc
    fdtd(fE, fH, p);

    // print 
    for (int j = 0; j < p.N; ++j) {
      for (int k = 0; k < p.N; ++k)
	out << fH[p.N*p.N*p.N * DIM + p.N*p.N * i + p.N * j + k] << " ";
      out << std::endl;
    }
  }
}


int main() {
  fdm_test();
  fdtd_test();
}
