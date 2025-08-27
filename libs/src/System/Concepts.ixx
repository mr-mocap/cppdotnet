module;

export module System:Concepts;

export import System:Exception;
import <concepts>;
export import <string>;


namespace System::Concepts
{

template <typename T>
concept HasValueType = requires { typename T::value_type; };

template <typename T>
concept Comparable = requires(T Object, T OtherObject) {
    { Object.CompareTo(OtherObject) } -> std::same_as<int>; // Must return -1, 0, or 1 ( for <, ==, > )
};

template <typename T>
concept Equatable = requires(T Object, T OtherObject) {
    { Object.Equals(OtherObject) } -> std::same_as<bool>;
};

template <typename T>
concept Formattable = requires(T Object, const std::string &format) {
    { Object.ToString(format) } -> std::same_as<std::string>;
};

template <typename T>
concept Observer = requires(T Object, T NewData, Exception ExceptionObject) {
    { Object.OnCompleted() } -> std::same_as<void>;
    { Object.OnError(ExceptionObject) } -> std::same_as<void>;
    { Object.OnNext(NewData) } -> std::same_as<void>;
};

template <typename T>
concept Observable = requires(T Object) {
    Object.Subscribe();
};

template <typename T>
concept Parsable = requires(T Object, const std::string &s) {
    { Object.Parse(s) } -> std::same_as<T>;
    { Object.TryParse(s) } -> std::same_as<T>;
};

template <typename T>
concept Progress = requires(T Object, T NewValue) {
    { Object.Report(NewValue) } -> std::same_as<void>;
};

template <typename T>
concept Disposable = requires(T Object) {
    { Object.Dispose() } -> std::same_as<void>;
};

}