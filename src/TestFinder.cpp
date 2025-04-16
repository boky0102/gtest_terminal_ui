#include "TestFinder.h"
#include <linux/limits.h>


#include <cmath>
#include <cstdio>
#include <exception>
#include <format>
#include <string>
#include <utility>
#include <vector>
#include <filesystem>
#include <iostream>

#include <cctype>

#include "Types.h"

#ifdef __linux__
#include <unistd.h>
#endif

TestFinder::TestFinder(std::filesystem::path rootPath) : m_rootPath(rootPath) {
}

auto TestFinder::GetTestFiles()
    -> std::vector<TestExe> 
{ 
    return GatherTestData();
}

bool TestFinder::PathIsExecutable(const std::filesystem::path& path)
{

#ifdef __linux__

    const auto executable = access(path.c_str(), X_OK);
    
    if(executable == -1){
        return false;
    }

    return true;

#endif

// TODO: MAKE WINDOWS IMPLEMENTATION
#ifdef __WIN32


#endif

    return false;

};

auto TestFinder::ParseStdOutLine(char* line) -> std::pair<NameType, std::string>
{
    
    std::string name = "";

    while(*line != NULL){
        
        if(std::iscntrl(*line)){
            line++;
            continue;
        }

        name += *line;
        line++;
    }

    if(name.ends_with(".")){
        name.pop_back();
        return std::make_pair(NameType::SuiteName, name);
    }

    return std::make_pair(NameType::TestName, name);
}


auto TestFinder::GetTestNamesFromTestExe(TestExe &testExe) -> std::vector<Test>
{
    FILE* fp;
    char path[PATH_MAX];
    auto command = std::format("./{} --gtest_list_tests", testExe.name);
    fp = popen(command.c_str(), "r");

    if(fp == NULL){
        std::cout << "FP IS NULL ****** " << std::endl;
    }

    std::vector<Test> foundTests;

    // NOTE: TO OPTIMIZE
    bool isFirstLine = true;
    std::string currentSuite = "";
    while(fgets(path, PATH_MAX, fp) != NULL){

        if(isFirstLine){
            isFirstLine = false;
            continue;
        }

        const auto [type, name] = ParseStdOutLine(path);
        
        if(type == NameType::SuiteName){
            currentSuite.replace(0, name.size(), name);
            continue;
        }
        
        foundTests.emplace_back(Test{currentSuite, name});

        std::cout << currentSuite << " ... " << name << std::endl;
     }

    return foundTests;
};

auto TestFinder::GatherTestData() -> std::vector<TestExe>
{
    auto currentPath = std::filesystem::current_path();
    auto dirPaths = std::filesystem::recursive_directory_iterator(currentPath);

    std::vector<TestExe> tests{};
    tests.reserve(100000);

    for(const auto& path: dirPaths){
        if(path.is_directory()){
            continue;
        }

        if(!PathIsExecutable(path.path())){
            continue;
        }

        const auto fileName = path.path().filename();

        if(!fileName.string().starts_with("Test")){
            continue;
        }

        auto testExe = TestExe{fileName.string(), path.path()};


        auto testNames = GetTestNamesFromTestExe(testExe);
        tests.emplace_back(testExe);
    }

    return tests;
}


