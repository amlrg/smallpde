#include "fdm.hpp"
#include "types.hpp"

// Zero Dirichlet BC diffusion
Field fdm(const Field& inp, const Params<ProblemType::Diffusion>& p) {
  Field out = inp;
  Field wrk(inp.size());

  Real d = p.dt/p.dx/p.dx;
  
  using std::swap;
  for (int t = 0; t < p.timeSteps; ++t) {
    for (int i = 1; i < p.N-1; ++i) {
#pragma omp simd
      for (int j = 1; j < p.N-1; ++j) {
	wrk[p.N * i + j] = out[p.N * i + j] + d*(-4.*out[p.N * i + j]
		         + out[p.N * (i+1) + j] + out[p.N * i + (j+1)]
                         + out[p.N * (i-1) + j] + out[p.N * i + (j-1)]);
      }
    }
    swap(out, wrk);
  }

  return out;
}
