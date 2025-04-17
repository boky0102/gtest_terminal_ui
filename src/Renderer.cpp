#include "Renderer.h"

#include <vector>

#include "ITestFinder.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"

#include "iostream"

namespace RENDERER {

void HandleArrowDown(State& state) {

    // NOTE: Optimize with global view into found tests
    auto nTests = 0;
    for(const auto& testExe: state.test_names){
        for(const auto& test: testExe.tests){
            nTests++;
        }
    }

    if (state.select_pos < nTests - 1) {
        state.select_pos++;
    }
}

void HandleArrowUp(State& state) {
    if (state.select_pos >= 1) {
        state.select_pos--;
    }
}

void HandleChars(State& state, ftxui::Event& event, ITestFinder& testFinder) {
    state.search_txt += event.character();

    // NOTE: Filter tests here
}

void HandleDelete(State& state) {
    if (state.search_txt.size() > 0) {
        state.search_txt.pop_back();
    }
}

void SwitchHandles(ftxui::Event& event, State& state, ITestFinder& testFinder) {
    if (event == ftxui::Event::ArrowDown) {
        HandleArrowDown(state);
    } else if (event == ftxui::Event::ArrowUp) {
        HandleArrowUp(state);
    } else if (event == ftxui::Event::Backspace ||
               event == ftxui::Event::Delete) {
        HandleDelete(state);
    } else if (event.is_character()) {
        HandleChars(state, event, testFinder);
    }
}

// TODO: limit number of rendered elements when size is too big
// NOTE: This part is subject to change !!! current implementation is not finished
auto TransformSearchResultToDom(State& state) -> std::vector<ftxui::Element> {
    auto elements = std::vector<ftxui::Element>{};

    int i = 0;
    for (const auto& testExe : state.test_names) {

        for(const auto& test: testExe.tests){
             auto bgColor = i == state.select_pos
                           ? ftxui::Color::Palette16::Cyan
                           : ftxui::Color::Palette16::MagentaLight;

            elements.emplace_back(ftxui::text(test.name) | ftxui::bgcolor(bgColor));
            i++;
        }
    }

    return elements;
}

ftxui::Component Setup(State& state, ftxui::Component& input_element,
                       ITestFinder& testFinder) {

    // TODO: Add busy indicator somewhere while tests are being searched
    state.test_names = testFinder.GetTestFiles();

    auto renderer = ftxui::Renderer(input_element, [&]() {
        auto inputElement = ftxui::hbox(
            {ftxui::text("Search : ") | ftxui::bold, input_element->Render()});

        return ftxui::vbox({inputElement, ftxui::separator(),
                            ftxui::vbox(TransformSearchResultToDom(state))});
    });

    // Register events
    renderer |= ftxui::CatchEvent([&](ftxui::Event event) {
        SwitchHandles(event, state, testFinder);
        return true;
    });

    return renderer;
}

}  // namespace RENDERER
