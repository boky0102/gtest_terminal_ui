#pragma once

#include "ITestFinder.h"
#include "rocket.hpp"

class TestRunner : public ITestRunner
{
   public:

    ~TestRunner() = default;

    TestRunner();
    void RunTest(TestExe test, std::string& testName) override;
    void ConnectTestOutputAvailableSignal(rocket::signal<void(std::string)>::slot_type);

   private:
    rocket::signal<void(std::string)> pushLine;
};
