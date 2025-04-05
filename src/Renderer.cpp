#include "Renderer.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"

namespace RENDERER {

// TODO: improve performance by not creating whole vector of ftxui elements on
// each render!

ftxui::Component Setup(State& state, ftxui::Component& input_element) {
    auto renderer = ftxui::Renderer(input_element, [&]() {
        auto inputElement = ftxui::hbox(
            {ftxui::text("Search : ") | ftxui::bold, input_element->Render()});

        return ftxui::vbox({inputElement, ftxui::separator()});
    });

    // Register events
    renderer |= ftxui::CatchEvent([&](ftxui::Event event) {
        // TODO: add custom handlers in separate functions
        if (event == ftxui::Event::ArrowUp) {
            state.select_pos++;
        }

        state.select_pos++;

        return true;
    });

    return renderer;
}

}  // namespace RENDERER
