#pragma once

#include <cppdotnet/System/Diagnostics/Activity.hpp>
#include <string>
#include <string_view>
#include <optional>


namespace System::Diagnostics
{

class ActivityListener;

class ActivitySource final
{
public:
    ActivitySource(std::string_view name);
    ActivitySource(std::string_view name, std::string_view version);
   ~ActivitySource();

    std::string_view Name() const { return _name; }

    std::string_view Version() const { return _version; }

#if 0
    ? Tags() const { return _tags; }
#endif

    bool HasListeners() const;

    std::optional<Activity> CreateActivity(std::string_view  operation_name,
                                           ActivityKind      kind,
                                           ActivityContext  &parent_context,
                                           ActivityIdFormat  id_format);

    std::optional<Activity> CreateActivity(std::string_view operation_name,
                                           ActivityKind     kind);

    std::optional<Activity> StartActivity(std::string_view operation_name,
                                          ActivityKind     kind = ActivityKind::Internal);

    static void AddActivityListener(const ActivityListener &listener);

    void Dispose();
protected:
    std::string _name;
    std::string _version;
#if 0
                _tags;
#endif
};

}