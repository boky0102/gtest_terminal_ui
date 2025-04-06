#pragma once

#include "ITestFinder.h"
#include "State.h"
#include "ftxui/component/component_base.hpp"

namespace RENDERER {

// Setup render component
// -> its main purpose is to allow for dependency injection
//    of the input component for better testing
// -> setting up of the components to render based on state
// -> regitering of event handlers
ftxui::Component Setup(State& state, ftxui::Component& input_component,
                       ITestFinder& testFinder);

}  // namespace RENDERER
