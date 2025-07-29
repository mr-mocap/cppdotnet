#pragma once

#include "System/Diagnostics/DiagnosticSource.hpp"
#include "System/IDisposable.hpp"
#include "System/IObservable.hpp"
#include "System/IObserver.hpp"
#include "System/Collections/Generic/KeyValuePair.hpp"
#include "System/Collections/Generic/List.hpp"
#include <string>
#include <string_view>


namespace System::Diagnostics
{

class DiagnosticListener : public DiagnosticSource,
                           public IObservable<Collections::Generic::KeyValuePair<std::string, void *>>
{
public:
    DiagnosticListener(std::string_view name);
   ~DiagnosticListener();

    const std::string &Name() const { return _name; }

    bool IsEnabled() const override;
    bool IsEnabled(std::string_view name) const override;

    // IObservable<T> interface
    // AllListeners();

    virtual IDisposable Subscribe(IObserver<Collections::Generic::KeyValuePair<std::string, void *>> &observer) override;

    void Dispose();
protected:
    std::string _name;
    Collections::Generic::List<Collections::Generic::KeyValuePair<std::string, void *>> _observers;

    void WritePayload(std::string_view payload) override;
};

}