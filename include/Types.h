#pragma once

#include <string>
#include <paths.h>
#include <filesystem>
#include <vector>

struct Test{
    std::string group;
    std::string name;
};

struct TestExe {
    std::string name;
    std::filesystem::path path;
    std::vector<Test> tests;
};

