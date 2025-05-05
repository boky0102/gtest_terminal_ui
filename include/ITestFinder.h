#pragma once

#include <vector>

#include "Types.h"
#include "string"

class ITestFinder
{
   public:
    virtual auto GetTestFiles() -> std::vector<TestExe> = 0;
    virtual ~ITestFinder() {};
};

class ITestRunner
{
    public:
    virtual void RunTest(TestExe test, std::string& testName) = 0;
    virtual ~ITestRunner() {};
};
