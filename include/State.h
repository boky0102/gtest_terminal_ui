#pragma once

#include "ITestFinder.h"
#include "string"
#include "vector"

struct State {
    std::vector<TestInfo> test_names;
    int select_pos;
    std::string search_txt;
};
