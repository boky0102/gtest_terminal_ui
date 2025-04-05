#include "Renderer.h"
#include "State.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "gtest/gtest.h"

class TestDomState : public testing::Test
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
