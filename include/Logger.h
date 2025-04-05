#pragma once

#include "string"
#include "vector"

namespace UTIL {

class Log
{
   public:
    Log operator<<(std::string& message) {
        m_logs.push_back(message);
        return *this;
    }

    auto GetLogs() -> std::vector<std::string>;

   private:
    std::vector<std::string> m_logs;
};
}  // namespace UTIL
