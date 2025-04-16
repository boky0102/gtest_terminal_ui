#include "Logger.h"
#include "vector"
#include "ranges"
#include "iostream"

namespace UTIL {

void Log(std::vector<TestExe> &testExes){
    for (TestExe testExe : std::views::all(testExes)){
        
        std::cout << testExe.name << std::endl;
        
        std::cout << testExe.path << std::endl;

        for(Test testName : std::views::all(testExe.tests)){
            std::cout << "   " << testName.group << " . " << testName.name << std::endl;
        }

    }
}

// NOTE: not usable !! 
void Log(std::ranges::input_range auto&& data){
    for(const TestExe exe : data){
        std::cout << exe.name << std::endl;
        std::cout << exe.path << std::endl;

        for(Test testName : std::views::all(exe.tests)){
            std::cout << "   " << testName.group << " . " << testName.name << std::endl; 
        }

        std::cout << "-----------------------" << std::endl;
    }

    std:: cout << "###########################" << std::endl;
}

}
