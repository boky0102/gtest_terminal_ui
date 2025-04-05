#pragma once

#include "ftxui/dom/elements.hpp"

namespace ITEM {

struct ButtonProps {
    std::string text;
    bool selected;
};

ftxui::Element Create(ButtonProps props);
}  // namespace ITEM
