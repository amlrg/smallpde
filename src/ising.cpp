#include "types.hpp"
#include <iostream>

void ising(std::vector<int>& spin, const Params<ProblemType::Ising>& p) {
  for (int t = 0; t < p.steps; ++t)
    for (int i = 0; i < p.N; ++i)
      for (int j = 0; j < p.N; ++j)
	std::cout << ".";
}
