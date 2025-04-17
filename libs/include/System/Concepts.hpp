#pragma once

#include "System/Exception.hpp"
#include <string>
#include <concepts>


namespace System::Concepts
{

template <typename T>
concept HasValueType = requires { T::value_type; };

template <typename T>
concept IComparable = requires(T Object, T OtherObject) {
    { Object.CompareTo(OtherObject) } -> std::same_as<int>; // Must return -1, 0, or 1 ( for <, ==, > )
};

template <typename T>
concept IEquatable = requires(T Object, T OtherObject) {
    { Object.Equals(OtherObject) } -> std::same_as<bool>;
};

template <typename T>
concept IFormattable = requires(T Object, const std::string &format) {
    { Object.ToString(format) } -> std::same_as<std::string>;
};

template <typename T>
concept IObserver = requires(T Object, T NewData, Exception ExceptionObject) {
    { Object.OnCompleted() } -> std::same_as<void>;
    { Object.OnError(ExceptionObject) } -> std::same_as<void>;
    { Object.OnNext(NewData) } -> std::same_as<void>;
};

template <typename T>
concept IObservable = requires(T Object) {
    Object.Subscribe();
};

template <typename T>
concept IParsable = requires(T Object, const std::string &s) {
    { Object.Parse(s) } -> std::same_as<T>;
    { Object.TryParse(s) } -> std::same_as<T>;
};

template <typename T>
concept IProgress = requires(T Object, T NewValue) {
    { Object.Report(NewValue) } -> std::same_as<void>;
};

}