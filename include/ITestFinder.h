#pragma once

#include <string>
#include <vector>

struct TestInfo {
    std::string name;
    std::string parent;
};

class ITestFinder
{
   public:
    virtual auto GetTestNames(std::string searchStr)
        -> std::vector<TestInfo> = 0;
    virtual ~ITestFinder() {};
};

class ITestRunner
{
    virtual void RunTest(TestInfo test);
};
