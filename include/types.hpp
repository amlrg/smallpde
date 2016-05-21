#pragma once
#include <vector>
#include <array>

using Real  = float;
using Field = std::vector<Real>;

enum class ProblemType { Diffusion, Maxwell };

template <ProblemType T>
struct Params {
// should not compile
};

template <> // 2D
struct Params<ProblemType::Diffusion> {
  int N;
  int timeSteps;
  Real dx;
  Real dt;
};

template <> // 3D
struct Params<ProblemType::Maxwell> {
  int N;
  int timeSteps;
  Real dx;
  Real dt;
};
