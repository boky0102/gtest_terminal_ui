#include <vector>

#include "Renderer.h"
#include "State.h"
#include "TestFinderMock.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "gmock/gmock-nice-strict.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class TestDomState : public testing::Test
{
   protected:
    void SetupStateAndInput() {
        m_state = {{{"one", "one"}, {"two", "two"}, {"three", "three"}}, 0, ""};
        m_inputElement = ftxui::Input(m_state.search_txt);
        m_renderer = RENDERER::Setup(m_state, m_inputElement, m_testFinderMock);
    }

    void SetupMocks() {
        // clang-format off
        ON_CALL(m_testFinderMock, GetTestNames(testing::_))
            .WillByDefault(
                testing::Return(std::vector<TestInfo>{
                    {"Tests1", "test1"},
                    {"Tests1", "test2"},
                    {"Kfc", "chicken_flies"},
                    {"Kfc", "fly_chicken"},
                    {"Kfc", "fly_chicken_run"}
                }));
        // clang-format on
    }

    ftxui::Component m_inputElement;

    ftxui::Component m_renderer;

    State m_state;

    testing::NiceMock<TestFinderMock> m_testFinderMock;
};

TEST_F(TestDomState, TestRender) {
    SetupStateAndInput();
    SetupMocks();

    m_renderer->OnEvent(ftxui::Event::Character('t'));

    EXPECT_EQ(m_state.test_names.size(), 2);
}
