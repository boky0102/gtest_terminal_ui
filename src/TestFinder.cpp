#include "TestFinder.h"

#include <vector>
#include <filesystem>

#include "Types.h"

TestFinder::TestFinder(std::filesystem::path rootPath) : m_rootPath(rootPath) {
}

auto TestFinder::GetTestFiles()
    -> std::vector<TestExe> 
{ 
    return GatherTestData();
}


auto TestFinder::GatherTestData() -> std::vector<TestExe>
{
    auto currentPath = std::filesystem::current_path();
    auto dirPaths = std::filesystem::recursive_directory_iterator(currentPath);

    std::vector<TestExe> tests{};
    tests.reserve(100000);


    for(const auto& path: dirPaths){
        const auto fileName = path.path().filename();
        auto testExe = TestExe{fileName.string(), path.path()};
        tests.emplace_back(testExe);
    }

    return tests;
}
