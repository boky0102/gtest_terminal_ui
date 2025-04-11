#pragma once

#include "Types.h"
#include "string"
#include "vector"

struct State {
    std::vector<TestExe> test_names;
    int select_pos;
    std::string search_txt;
};
