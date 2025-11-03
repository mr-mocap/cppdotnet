#include <cppdotnet/System/Diagnostics/ActivitySource.hpp>
#include <cppdotnet/System/Diagnostics/ActivityListener.hpp>
#include <cstdlib>
#include <cassert>

namespace TestActivitySource
{

void ActivitySourceHasNameGivenInConstructor()
{
    System::Diagnostics::ActivitySource source("Example Activity Source");

    assert( source.Name() == "Example Activity Source" );
}

void ActivitySourceHasNameAndVersionGivenInConstructor()
{
    System::Diagnostics::ActivitySource source("Example Activity Source", "1.0.0");

    assert( source.Name() == "Example Activity Source" );
    assert( source.Version() == "1.0.0" );
}

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

void AddActivityListenerThatListensToActivityNameMeansSourceHasListeners()
{
    System::Diagnostics::ActivitySource source("Test Source");
    System::Diagnostics::ActivityListener listener;

    listener.ShouldListenTo([](const System::Diagnostics::ActivitySource &src) {
        return src.Name() == "Test Source";
    });
    System::Diagnostics::ActivitySource::AddActivityListener(listener);

    assert( source.HasListeners() );
}

void AddActivityListenerThatDoesNotListenToActivityNameMeansSourceHasNoListeners()
{
    System::Diagnostics::ActivitySource source("Test Source");
    System::Diagnostics::ActivityListener listener;

    listener.ShouldListenTo([](const System::Diagnostics::ActivitySource &src) {
        return src.Name() == "Other Source";
    });
    System::Diagnostics::ActivitySource::AddActivityListener(listener);

    assert( !source.HasListeners() );
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
    ActivitySourceHasNameGivenInConstructor();
    ActivitySourceHasNameAndVersionGivenInConstructor();
    ActivitySourceHasNoListenersWhenConstructed();
    AddActivityListenerThatListensToActivityNameMeansSourceHasListeners();
    AddActivityListenerThatDoesNotListenToActivityNameMeansSourceHasNoListeners();
    StartingActivityWithNoActivityListenersRegistered();
    StartingActivityWithOneActivityListenerRegisteredThatListensForTheSource();
    StartingActivityWithOneActivityListenerRegisteredThatDoesNotListenForTheSource();
}

}

int main(void)
{
    //TestActivitySource::Run();
    return EXIT_SUCCESS;
}
