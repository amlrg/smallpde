#include "fdm.hpp"
#include "types.hpp"

// Zero Dirichlet BC diffusion with source
Field fdm(const Field& inp, const Params<ProblemType::Diffusion>& p) {
  Field out = inp;
  Field wrk(inp.size());

  const Real d = p.D*p.dt/p.dx/p.dx;
  
  using std::swap;
  for (int t = 0; t < p.timeSteps; ++t) {
    // df/dt = D nabla^2 f + rho
    for (int i = 1; i < p.N-1; ++i) {
#pragma omp simd
      for (int j = 1; j < p.N-1; ++j) {
	wrk[p.N * i + j] = out[p.N * i + j] + d*(-4.*out[p.N * i + j]
		         + out[p.N * (i+1) + j] + out[p.N * i + (j+1)]
                         + out[p.N * (i-1) + j] + out[p.N * i + (j-1)]);
      }
    }
    wrk[p.N * p.N/2 + p.N/2] += 1;
    swap(out, wrk);
  }

  return out;
}
