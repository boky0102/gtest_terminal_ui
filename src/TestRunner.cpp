#include "TestRunner.h"

#include <linux/limits.h>

#include <cstdio>
#include <iostream>

#include "Types.h"
#include "rocket.hpp"

TestRunner::TestRunner() {
}

void TestRunner::RunTest(TestExe testExe, std::string& testName) {
    FILE* fp;
    char path[PATH_MAX];
    const auto command =
        std::format("./{} --gtest_filter=*{}*", testExe.name, testName);
    fp = popen(command.c_str(), "r");

    if (fp == NULL) {
        std::cout << "Can't open the file" << std::endl;
    }

    while (fgets(path, PATH_MAX, fp) != NULL) {
        pushLine(path);
    }
}

void TestRunner::ConnectTestOutputAvailableSignal(
    rocket::signal<void(std::string)>::slot_type slot) {
    pushLine.connect(slot);
}
