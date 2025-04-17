#pragma once

#include "System/Concepts.hpp"
#include "System/Collections/Generic/KeyValuePair.hpp"
#include <concepts>


namespace System::Collections::Generic::Concepts
{

template <typename ContainerT, typename ValueT>
concept ICollection = requires(ContainerT Object, ContainerT OtherObject) {
    { ContainerT::value_type } -> std::same_as<ValueT>;

    { Object.Count() } -> std::same_as<int>; // Must return -1, 0, or 1 ( for <, ==, > )
    { Object.IsReadOnly() } -> std::same_as<bool>;
    { Object.Add(OtherObject) } -> std::same_as<void>;
    { Object.Clear() } -> std::same_as<void>;
    { Object.Contains(OtherObject) } -> std::same_as<bool>;
    //{ Object.CopyTo() } -> std::same_as<bool>;
    { Object.Remove(OtherObject) } -> std::same_as<bool>;
};

template <typename T>
concept IComparer = requires(T Object, T OtherObject) {
    { Object.Compare(Object, OtherObject) } -> std::same_as<int>;
};

template <typename T, typename KeyT, typename ValueT>
concept IDictionaryOnly = requires(T Object, const KeyT &key) {
    { T::value_type } -> std::same_as< KeyValuePair<KeyT, ValueT> >;
    { T::key_type } -> std::same_as<KeyT>;
    { T::mapped_type } -> std::same_as<ValueT>;
    T::KeyCollection;
    T::ValueCollection;

    { Object.Count() } -> std::same_as<int>;
    { Object.IsReadOnly() } -> std::same_as<bool>;
    { Object[key] } -> std::same_as<ValueT &>;
    { Object.Keys() } -> std::same_as<typename T::KeyCollection>;
    { Object.Values() } -> std::same_as<typename T::ValueCollection>;
};

template <typename T, typename KeyT, typename ValueT>
concept IDictionary = IDictionaryOnly<T, KeyT, ValueT> &&
                      ICollection<T, typename T::value_type>;
    // NOTE: Also implements ICollection<KeyValuePair<KeyT, ValueT>>

template <typename T>
concept IEqualityComparer = requires(T Object, T OtherObject) {
    { Object.Equals(Object, OtherObject) } -> std::same_as<int>;
};

}