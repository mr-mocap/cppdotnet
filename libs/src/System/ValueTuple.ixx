module;

export module System:ValueTuple;

export import <tuple>;

export
{

namespace System
{

template <typename ...ArgTypes>
struct ValueTuple : std::tuple<ArgTypes ...>
{
    using std::tuple<ArgTypes ...>::tuple;

    template <std::size_t index>
    auto Item()
    {
        return std::get<index>(*this);
    }

    static auto Create(auto &...args)
    {
        return ValueTuple{ std::make_tuple(args...) };
    }
};

}

}