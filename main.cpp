#include <memory>

#include "Renderer.h"
#include "State.h"
#include "TestFinder.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"

int main() {
    State state;

    state.select_pos = 0;
    state.search_txt = "";
    state.test_names = {{"One", "one"}, {"Two", "two"}, {"Three", "Three"}};

    auto input_element = ftxui::Input(&state.search_txt, "Search");

    auto testFinder = std::make_unique<TestFinder>("C://");

    auto renderer = RENDERER::Setup(state, input_element, *testFinder);

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.TrackMouse(false);
    screen.Loop(renderer);
}
