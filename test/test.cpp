#include "Renderer.h"
#include "State.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "gtest/gtest.h"

// TODO: Try to remove dependency on the input component
// since you can trigger states from the outside without
// dependency injection of the input componenet!
class TestEvent : public testing::Test
{
   protected:
    void SetupStateAndInput() {
        m_inputElement = ftxui::Input(state.search_txt);
        m_renderer = RENDERER::Setup(state, m_inputElement);
    }

    State state{{"one", "two", "three"}, 0, ""};

    ftxui::Component m_inputElement;

    ftxui::Component m_renderer;
};

TEST_F(TestEvent, TestArrowDown) {
    SetupStateAndInput();

    auto const stateBefore = state.select_pos;

    m_renderer->OnEvent(ftxui::Event::Character('q'));

    auto const stateAfter = state.select_pos;

    EXPECT_EQ(stateAfter - 1, stateBefore);
}
