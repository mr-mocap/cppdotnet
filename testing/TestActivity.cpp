#include <cppdotnet/System/Console.hpp>
#include <cppdotnet/System/IO/TextWriter.hpp>
#include <cppdotnet/System/Diagnostics/ActivitySource.hpp>
#include <cppdotnet/System/Diagnostics/ActivityListener.hpp>
#include <cstdlib>
#include <cassert>

namespace TestActivity
{

void ActivitySourceHasNoListenersWhenConstructed()
{
    System::Diagnostics::ActivitySource source("Example Activity Source");

    assert( !source.HasListeners() );
}

void StartingActivityWithNoActivityListenersRegistered()
{
    System::Diagnostics::ActivitySource source("Example Activity Source");
    std::optional<System::Diagnostics::Activity> activity = source.StartActivity("Example Operation");

    assert( !activity );
}

void StartingActivityWithOneActivityListenerRegisteredThatListensForTheSource()
{
    System::Diagnostics::ActivitySource source("Example Activity Source");

    System::Diagnostics::ActivityListener listener;

    listener.ShouldListenTo([](const System::Diagnostics::ActivitySource &src) {
        return src.Name() == "Example Activity Source";
    });
    System::Diagnostics::ActivitySource::AddActivityListener(listener);

    assert( source.HasListeners() );

    std::optional<System::Diagnostics::Activity> activity = source.StartActivity("Example Operation");

    assert( activity );
}

void StartingActivityWithOneActivityListenerRegisteredThatDoesNotListenForTheSource()
{
    System::Diagnostics::ActivitySource source("Blah");

    System::Diagnostics::ActivityListener listener;

    listener.ShouldListenTo([](const System::Diagnostics::ActivitySource &src) {
        return src.Name() == "Some Other Activity Source";
    });
    System::Diagnostics::ActivitySource::AddActivityListener(listener);

    assert( !source.HasListeners() );

    std::optional<System::Diagnostics::Activity> activity = source.StartActivity("Example Operation");

    assert( !activity );
}

void Run()
{
    ActivitySourceHasNoListenersWhenConstructed();
    StartingActivityWithNoActivityListenersRegistered();
    StartingActivityWithOneActivityListenerRegisteredThatListensForTheSource();
    StartingActivityWithOneActivityListenerRegisteredThatDoesNotListenForTheSource();
}

}

int main(void)
{
    TestActivity::Run();
    return EXIT_SUCCESS;
}