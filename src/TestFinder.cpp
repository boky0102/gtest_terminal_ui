#include "TestFinder.h"

#include <ranges>
#include <string>
#include <vector>

TestFinder::TestFinder(std::string rootPath) : m_rootPath(rootPath) {
}

auto TestFinder::GetTestNames(std::string searchString)
    -> std::vector<TestInfo> {
    std::vector<TestInfo> vec;

    return vec;
}
