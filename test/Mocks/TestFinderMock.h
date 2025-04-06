#include "ITestFinder.h"
#include "gmock/gmock.h"
#include "vector"

class TestFinderMock : public ITestFinder
{
   public:
    MOCK_METHOD(std::vector<TestInfo>, GetTestNames, (std::string), (override));
};
