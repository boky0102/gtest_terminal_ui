#include "string"
#include "vector"

namespace UTIL
{

class Log {
public:
   void operator<<(std::string& message){
      m_logs.push_back(message);       
   }

   auto GetLogs() -> std::vector<std::string>;
private:
   std::vector<std::string> m_logs;

};
}

