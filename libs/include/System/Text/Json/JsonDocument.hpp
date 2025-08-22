#include <string_vew>


namespace System::Text::Json
{

class JsonDocument
{
public:

    static JsonDocument Parse(std::string_view data);
protected:
};

}