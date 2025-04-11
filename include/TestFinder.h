#pragma once

#include <filesystem>
#include "ITestFinder.h"

class TestFinder : public ITestFinder
{
   public:
    TestFinder(std::filesystem::path path);
    ~TestFinder() = default;

    auto GetTestFiles() -> std::vector<TestExe> override;

   private:
    auto GatherTestData() -> std::vector<TestExe>;

    std::filesystem::path m_rootPath;
};
