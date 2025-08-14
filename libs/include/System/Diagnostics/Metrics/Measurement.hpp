
namespace System::Diagnostics::Metrics
{

template <class T>
struct Measurement
{
    Measurement(const T &value) : Value( value ) { }

    T Value;
};

}