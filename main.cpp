#include <cstdlib>
#include <string>
#include <vector>

#include "TestFinder.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "string"

int main() {
    std::string input;

    int selected_element = -1;
    int previous_element = -1;

    std::vector<std::string> list{"one line", "two line", "three line"};

    std::vector<ftxui::Element> list_tst{ftxui::text("hi"), ftxui::text("bye"),
                                         ftxui::text("bla")};

    std::vector<ftxui::Element> elements;
    elements.reserve(list.size());

    for (auto &elem : list) {
        elements.push_back(ftxui::text(elem));
    }
    ftxui::Component input_search = ftxui::Input(&input, "Search");

    auto components = ftxui::Container::Vertical({input_search});

    auto renderer = ftxui::Renderer(components, [&] {
        elements[selected_element + 1] |= ftxui::bgcolor(ftxui::Color::Blue);
        if (previous_element > 0) {
            elements[previous_element] |=
                ftxui::bgcolor(ftxui::Color::Aquamarine1);
        }

        previous_element = selected_element;

        auto results = ftxui::frame(ftxui::vbox(elements));
        return ftxui::vbox({ftxui::hbox(ftxui::text("Search : ") | ftxui::bold,
                                        input_search->Render()),
                            ftxui::separator(),
                            results | ftxui::bgcolor(ftxui::Color::Cyan)});
    });

    renderer |= ftxui::CatchEvent([&](ftxui::Event event) {
        if (event == ftxui::Event::ArrowUp) {
            elements.emplace_back(ftxui::text(event.character()));
            selected_element--;
            return true;
        } else if (event == ftxui::Event::ArrowDown) {
            elements.emplace_back(ftxui::text(event.character()));

            selected_element++;
            return true;
        } else if (event.character() == "q") {
            selected_element++;
            return true;
        }

        return false;
    }

    );

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.Loop(renderer);

    elements.clear();
}
