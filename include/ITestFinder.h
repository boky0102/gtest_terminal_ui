#pragma once

#include <vector>
#include "Types.h"

class ITestFinder
{
   public:
    virtual auto GetTestFiles() -> std::vector<TestExe> = 0;
    virtual ~ITestFinder() {};
};

class ITestRunner
{
    virtual void RunTest(TestExe test);
};
