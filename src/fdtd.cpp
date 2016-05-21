#include "fdtd.hpp"
#include "types.hpp"
#include <cmath>

#define IND(DIM,i,j,k) p.N*p.N*p.N*(DIM) + p.N*p.N*(i) + p.N*(j) + (k)

// TODO: should clean up, and make sure it actually works (and add PME)
// solves Maxwell's equations with current in z dir, simulating a simple antenna
void fdtd(Field& E, Field& H,const Params<ProblemType::Maxwell>& p) {
  Real d = p.dt/p.dx;

  for (int t = 0; t < p.timeSteps; ++t) {
    for (int i = 1; i < p.N; ++i) {
      for (int j = 1; j < p.N; ++j) {
#pragma omp simd
	for (int k = 1; k < p.N; ++k) {
	  E[IND(0,i,j,k)] += d*( (H[IND(2,i,j,k)] - H[IND(2,i,j-1,k)]) - (H[IND(1,i,j,k)] - H[IND(1,i,j,k-1)]) );
	  E[IND(1,i,j,k)] += d*( (H[IND(0,i,j,k)] - H[IND(0,i,j,k-1)]) - (H[IND(2,i,j,k)] - H[IND(2,i-1,j,k)]) );
	  E[IND(2,i,j,k)] += d*( (H[IND(1,i,j,k)] - H[IND(1,i-1,j,k)]) - (H[IND(0,i,j,k)] - H[IND(0,i,j-1,k)]) );
	  // current Jz:
	  E[IND(2,i,j,k)] += p.dt * 10*std::sin(2*3.14*t/1000.)*std::exp(-p.dx*p.dx*((i-p.N/2)*(i-p.N/2)+(j-p.N/2)*(j-p.N/2)+(k-p.N/2)*(k-p.N/2))/0.001);
	}
      }
    }
    for (int i = 0; i < p.N-1; ++i) {
      for (int j = 0; j < p.N-1; ++j) {
#pragma omp simd
	for (int k = 0; k < p.N-1; ++k) {
	  H[IND(0,i,j,k)] -= d*( (E[IND(2,i,j+1,k)] - E[IND(2,i,j,k)]) - (E[IND(1,i,j,k+1)] - E[IND(1,i,j,k)]) );
	  H[IND(1,i,j,k)] -= d*( (E[IND(0,i,j,k+1)] - E[IND(0,i,j,k)]) - (E[IND(2,i+1,j,k)] - E[IND(2,i,j,k)]) );
	  H[IND(2,i,j,k)] -= d*( (E[IND(1,i+1,j,k)] - E[IND(1,i,j,k)]) - (E[IND(0,i,j+1,k)] - E[IND(0,i,j,k)]));
	}
      }
    }
  }
}
