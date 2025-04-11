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

}

