#include <iostream>
#include <memory>

#include "Renderer.h"
#include "State.h"
#include "TestFinder.h"
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

        m_testFinder = std::make_unique<TestFinder>("C");

        auto fakeExe = TestExe{"testExe", "/path", {{"TestSuite1", "TestOne"}, {"TestSuite2", "TestTwo"}, {"TestSuite3", "TestThree"}}};
        state.test_names = {fakeExe, fakeExe, fakeExe};
        m_renderer = RENDERER::Setup(state, m_inputElement, *m_testFinder);
    }

    State state{{}, 0, ""};

    ftxui::Component m_inputElement;

    std::unique_ptr<TestFinder> m_testFinder;
    ftxui::Component m_renderer;
};

TEST_F(TestEvent, TestArrowDown) {
    SetupStateAndInput();

    auto const stateBefore = state.select_pos;

    m_renderer->OnEvent(ftxui::Event::ArrowDown);

    auto const stateAfter = state.select_pos;

    EXPECT_EQ(stateAfter - 1, stateBefore);

    state.select_pos = state.test_names.size() - 1;
    m_renderer->OnEvent(ftxui::Event::ArrowDown);

    EXPECT_EQ(state.select_pos, static_cast<int>(state.test_names.size()) - 1);
}

TEST_F(TestEvent, TestArrowUp) {
    SetupStateAndInput();

    auto stateBefore = state.select_pos;

    ASSERT_EQ(stateBefore, 0);
    m_renderer->OnEvent(ftxui::Event::ArrowUp);

    EXPECT_EQ(state.select_pos, 0);

    state.select_pos = 1;
    stateBefore = state.select_pos;
    m_renderer->OnEvent(ftxui::Event::ArrowUp);

    EXPECT_EQ(state.select_pos, stateBefore - 1);
}

TEST_F(TestEvent, TestInputElement) {
    SetupStateAndInput();

    ASSERT_EQ(state.search_txt, "");

    m_renderer->OnEvent(ftxui::Event::Character('q'));
    m_renderer->OnEvent(ftxui::Event::Character('w'));
    m_renderer->OnEvent(ftxui::Event::Character('e'));

    EXPECT_EQ(state.search_txt, "qwe");

    m_renderer->OnEvent(ftxui::Event::Delete);
    EXPECT_EQ(state.search_txt, "qw");

    m_renderer->OnEvent(ftxui::Event::Backspace);
    EXPECT_EQ(state.search_txt, "q");

    m_renderer->OnEvent(ftxui::Event::Backspace);
    m_renderer->OnEvent(ftxui::Event::Backspace);

}
