#pragma once

#include <filesystem>
#include "ITestFinder.h"
#include "utility"
#include "Types.h"
#include "vector"

enum NameType {
   SuiteName,
   TestName
};

class TestFinder : public ITestFinder
{
   public:
    TestFinder(std::filesystem::path path);
    ~TestFinder() = default;

    auto GetTestFiles() -> std::vector<TestExe> override;

   private:
    auto GatherTestData() -> std::vector<TestExe>;
    bool PathIsExecutable(const std::filesystem::path& path);
    auto GetTestNamesFromTestExe(TestExe& testExe) -> std::vector<Test>;
    auto ParseStdOutLine(char* line) -> std::pair<NameType, std::string>;

    std::filesystem::path m_rootPath;
};
