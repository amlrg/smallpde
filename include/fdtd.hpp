#pragma once
#include "types.hpp"

void fdtd(Field& E, Field& H, const Params<ProblemType::Maxwell>& p);
