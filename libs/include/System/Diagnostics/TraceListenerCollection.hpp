#pragma once

#include <set>
#include <string>


namespace System::Diagnostics
{

class TraceListener;

class TraceListenerCollection
{
public:
    TraceListenerCollection() = default;

    TraceListener *operator [](size_t index);
    TraceListener *operator [](const std::string_view name);

    size_t Count() const { return _list.size(); }

    int  Add(TraceListener *listener);
    void Remove(TraceListener *listener);
    void Remove(const std::string_view name);

    void Clear();

    bool Contains(TraceListener *listener);

    size_t IndexOf(TraceListener *listener);

    // C++ iterator adaptation section
    using value_type             = TraceListener *;
    using iterator               = std::set<TraceListener *>::iterator;
    using const_iterator         = std::set<TraceListener *>::const_iterator;
    using reverse_iterator       = std::set<TraceListener *>::reverse_iterator;
    using const_reverse_iterator = std::set<TraceListener *>::const_reverse_iterator;

    iterator       begin()       { return _list.begin(); }
    const_iterator begin() const { return _list.begin(); }
    const_iterator cbegin() const noexcept { return _list.cbegin(); }

    iterator       end()       { return _list.end(); }
    const_iterator end() const { return _list.end(); }
    const_iterator cend() const noexcept { return _list.cend(); }

    reverse_iterator       rbegin()        { return _list.rbegin(); }
    const_reverse_iterator rbegin()  const { return _list.rbegin(); }
    const_reverse_iterator crbegin() const noexcept { return _list.crbegin(); }

    reverse_iterator       rend()       { return _list.rend(); }
    const_reverse_iterator rend() const { return _list.rend(); }
    const_reverse_iterator crend() const noexcept { return _list.crend(); }
private:
    std::set<TraceListener *> _list;

    static void InitializeListener(TraceListener *listener);
};

}