#include "ITestFinder.h"
#include "gmock/gmock.h"
#include "vector"
#include "Types.h"

class TestFinderMock : public ITestFinder
{
   public:
    MOCK_METHOD(std::vector<TestExe>, GetTestFiles, (), (override));
};



