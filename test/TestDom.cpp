#include <filesystem>
#include <memory>
#include <vector>

#include "Renderer.h"
#include "State.h"
#include "TestFinderMock.h"
#include "TestRunner.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "gmock/gmock-nice-strict.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "TestRunner.h"

class TestDomState : public testing::Test
{
   protected:
    void SetupStateAndInput() {
        m_state = {{},0, ""};
        m_inputElement = ftxui::Input(m_state.search_txt);
        m_testRunner = std::make_unique<TestRunner>();

        m_renderer = RENDERER::Setup(m_state, m_inputElement, m_testFinderMock, *m_testRunner);
    }

    void SetupMocks() {
        auto bin1 = std::filesystem::current_path().append("TestFake1");
        auto bin2 = std::filesystem::current_path().append("TestFake2");
        auto bin3 = std::filesystem::current_path().append("TestFake3");


        ASSERT_TRUE(bin1.has_filename());
        ASSERT_TRUE(bin2.has_filename());
        ASSERT_TRUE(bin3.has_filename());

        // clang-format off
        auto fakeTest1Exe = TestExe{
            "TestFake1",
            bin1,
            {{"FakeSuite1", "FakeTest1"}}
        };

        auto fakeTest2Exe = TestExe{
            "TestFake2",
            bin2,
            {{"FakeSuite2", "FakeTest2"}, {"FakeSuite2", "FakeTest3"}}
        };

        auto fakeTest3Exe = TestExe{
            "TestFake3",
            bin3,
            {{"FakeSuite3", "FakeTest5"}, {"FakeSuite4", "FakeTest6"}, {"FakeSuite4", "FakeTest7"}}
        };
        // clang-format on

        auto fakeTestExes = std::vector<TestExe>{fakeTest1Exe, fakeTest2Exe, fakeTest3Exe};

        ON_CALL(m_testFinderMock, GetTestFiles())
            .WillByDefault(testing::Return(fakeTestExes));
    }

    ftxui::Component m_inputElement;

    ftxui::Component m_renderer;

    State m_state;

    testing::NiceMock<TestFinderMock> m_testFinderMock;
    std::unique_ptr<TestRunner> m_testRunner;

};

// NOTE: Here you can create tests with test mocked functionality
