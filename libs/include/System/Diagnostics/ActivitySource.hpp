#include "System/Diagnostics/Activity.hpp"
#include <string>
#include <string_view>


namespace System::Diagnostics
{

class ActivityListener;

class ActivitySource final
{
public:
    ActivitySource(std::string_view name)
        :
        _name( name )
    {
    }

    ActivitySource(std::string_view name, std::string_view version)
        :
        _name( name ),
        _version( version )
    {
    }

    std::string_view Name() const { return _name; }

    std::string_view Version() const { return _version; }

    bool HasListeners() const;

    Activity CreateActivity(std::string_view  name,
                            ActivityKind      kind,
                            ActivityContext  &parent_context,
                            ActivityIdFormat  id_format);

    static void AddActivityListener(const ActivityListener &listener);
protected:
    std::string _name;
    std::string _version;
};

}