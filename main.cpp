#include "Renderer.h"
#include "State.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"

int main() {
    State state;

    auto input_element = ftxui::Input(&state.search_txt, "Search");

    auto renderer = RENDERER::Setup(state, input_element);

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.TrackMouse(false);
    screen.Loop(renderer);
}
