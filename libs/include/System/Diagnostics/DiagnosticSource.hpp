#include <string_view>


namespace System::Diagnostics
{

class DiagnosticSource
{
public:
    DiagnosticSource() = default;

    virtual bool IsEnabled(std::string_view name);

    template <typename T>
    Activity &StartActivity(Activity &activity, const T &args);

    template <typename T>
    void StopActivity(Activity &activity, const T &args);

    template <typename T>
    void Write(std::string_view name, const T &value);

protected:
    virtual void WritePayload(std::string_view payload) = 0;
};

}