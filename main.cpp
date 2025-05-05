#include <memory>
#include <string>

#include "Renderer.h"
#include "State.h"
#include "TestFinder.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "TestRunner.h"

int main() {
    State state;

    state.select_pos = 0;
    state.search_txt = "";

    auto input_element = ftxui::Input(&state.search_txt, "Search");

    auto testFinder = std::make_unique<TestFinder>("C://");

    auto testRunner = std::make_unique<TestRunner>();
    auto renderer = RENDERER::Setup(state, input_element, *testFinder, *testRunner);

    auto screen = ftxui::ScreenInteractive::Fullscreen();

    testRunner->ConnectTestOutputAvailableSignal([&](std::string output){
        state.output.emplace_back(std::move(output));
        screen.Post(ftxui::Event::Special("OUTPUT"));
        std::cout << "Executed " << std::endl;
    });

    screen.TrackMouse(false);
    screen.Loop(renderer);

    return 1;
}
