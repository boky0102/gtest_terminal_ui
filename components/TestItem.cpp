#include "TestItem.h"

#include "ftxui/dom/elements.hpp"
#include "ftxui/dom/node.hpp"
#include "ftxui/screen/color.hpp"

namespace ITEM {

ftxui::Element Create(ButtonProps props) {
    auto bg = ftxui::bgcolor(props.selected ? ftxui::Color::BlueViolet
                                            : ftxui::Color::DarkSlateGray3);
    return ftxui::text(props.text) | bg;
}

}  // namespace ITEM
