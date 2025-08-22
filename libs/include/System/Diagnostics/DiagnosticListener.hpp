#include "System/Diagnostics/DiagnosticSource.hpp"
#include <string>


namespace System::Diagnostics
{

class DiagnosticListener : public DiagnosticSource
{
public:
    DiagnosticListener(std::string_view name);

    const std::string &Name() const { return _name; }

    // IObservable<T> interface
    Subscribe();
protected:
    std::string _name;
};

}