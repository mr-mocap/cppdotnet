#include "System/Concepts.hpp"
#include "System/Collections/Generic/KeyValuePair.hpp"
#include <concepts>


namespace System::Collections::Generic::Concepts
{

template <typename ContainerT, typename ValueT>
concept Collection = requires(ContainerT Object, ValueT Item) {
    typename ContainerT::value_type;
    { ContainerT::value_type } -> std::same_as<ValueT>;

    { Object.Count() } -> std::same_as<int>; // Must return -1, 0, or 1 ( for <, ==, > )
    { Object.IsReadOnly() } -> std::same_as<bool>;
    { Object.Add(Item) } -> std::same_as<void>;
    { Object.Clear() } -> std::same_as<void>;
    { Object.Contains(Item) } -> std::same_as<bool>;
    //{ Object.CopyTo() } -> std::same_as<bool>;
    { Object.Remove(Item) } -> std::same_as<bool>;
};

template <typename T>
concept Comparer = requires(T Object, T OtherObject) {
    { Object.Compare(Object, OtherObject) } -> std::same_as<int>;
};

#if 0
template <typename T, typename KeyT, typename ValueT>
concept DictionaryOnly = requires(T Object, const KeyT &key) {
    typename T::value_type;
    typename T::key_type;
    typename T::mapped_type;
    { T::value_type } -> std::same_as< KeyValuePair<KeyT, ValueT> >;
    { T::key_type } -> std::same_as<KeyT>;
    { T::mapped_type } -> std::same_as<ValueT>;

    typename T::KeyCollection;
    typename T::ValueCollection;

    { Object.Count() } -> std::same_as<int>;
    { Object.IsReadOnly() } -> std::same_as<bool>;
    { Object[key] } -> std::same_as<ValueT &>;
    { Object.Keys() } -> std::same_as<typename T::KeyCollection>;
    { Object.Values() } -> std::same_as<typename T::ValueCollection>;
};
#endif

#if 0
template <typename T, typename KeyT, typename ValueT>
concept Dictionary = DictionaryOnly<T, KeyT, ValueT> &&
                     Collection<T, Generic::KeyValuePair<KeyT, ValueT>>;
    // NOTE: Also implements ICollection<KeyValuePair<KeyT, ValueT>>
#else
template <typename T, typename KeyT, typename ValueT>
concept Dictionary = Collection<T, Generic::KeyValuePair<KeyT, ValueT>> &&
                     requires (T Object, const KeyT &key) {
                         typename T::KeyCollection;
                         typename T::ValueCollection;

                         { T::KeyCollection } -> std::same_as< Collection<T::KeyCollection, KeyT> >;
                         { T::ValueCollection } -> std::same_as< Collection<T::ValueCollection, ValueT> >;

                         { Object[key] } -> std::same_as<ValueT &>;
                         { Object.Keys() } -> std::same_as<typename T::KeyCollection>;
                         { Object.Values() } -> std::same_as<typename T::ValueCollection>;
                     }
#endif

template <typename T>
concept EqualityComparer = requires(T Object, T OtherObject) {
    { Object.Equals(Object, OtherObject) } -> std::same_as<int>;
};

}