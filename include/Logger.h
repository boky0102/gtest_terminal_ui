#pragma once

#include <ranges>
#include <vector>
#include "Types.h"
#include "vector"
#include "ranges"

namespace UTIL {

void Log(std::vector<TestExe> &testExes);


void Log(std::ranges::input_range auto&& data);

}; // namespace UTIL
