#include <cppdotnet/System/Progress.hpp>
#include <cppdotnet/System/Console.hpp>
#include <cassert>

int GlobalProgressValue = 0;
int GlobalNumberOfTimesActionCalled = 0;

void ActionCallback(int current)
{
    GlobalProgressValue = current;
    ++GlobalNumberOfTimesActionCalled;
}

namespace TestProgress
{

void ConstructWithAction()
{
    GlobalProgressValue = -1;
    GlobalNumberOfTimesActionCalled = 0;
    System::Action<int> my_action( ActionCallback );
    System::Progress<int> p( my_action );

    assert( GlobalProgressValue == -1 );
    assert( GlobalNumberOfTimesActionCalled == 0 );

    p.Report(0);

    assert( GlobalProgressValue == 0 );
    assert( GlobalNumberOfTimesActionCalled == 1 );

    p.Report(1);

    assert( GlobalProgressValue == 1 );
    assert( GlobalNumberOfTimesActionCalled == 2 );

    p.Report(2);

    assert( GlobalProgressValue == 2 );
    assert( GlobalNumberOfTimesActionCalled == 3 );
}

void ConstructWithExternalFunction()
{
    GlobalProgressValue = -1;
    GlobalNumberOfTimesActionCalled = 0;
    System::Progress<int> p( ActionCallback );

    assert( GlobalProgressValue == -1 );
    assert( GlobalNumberOfTimesActionCalled == 0 );

    p.Report(0);

    assert( GlobalProgressValue == 0 );
    assert( GlobalNumberOfTimesActionCalled == 1 );

    p.Report(1);

    assert( GlobalProgressValue == 1 );
    assert( GlobalNumberOfTimesActionCalled == 2 );

    p.Report(2);

    assert( GlobalProgressValue == 2 );
    assert( GlobalNumberOfTimesActionCalled == 3 );
}

void ConstructWithLambda()
{
    int logged_values = -1;
    int number_of_times_called = 0;
    System::Progress<int> p( [&](int current) { logged_values = current; ++number_of_times_called; } );

    assert( logged_values == -1 );
    assert( number_of_times_called == 0 );

    p.Report(0);

    assert( logged_values == 0 );
    assert( number_of_times_called == 1 );

    p.Report(1);

    assert( logged_values == 1 );
    assert( number_of_times_called == 2 );

    p.Report(2);

    assert( logged_values == 2 );
    assert( number_of_times_called == 3 );
}

void ConstructWithNoActionCausesReportToNotReportTheAction()
{
    GlobalProgressValue = -1;
    System::Progress<int> p;

    assert( GlobalProgressValue == -1 );

    p.Report(0);

    assert( GlobalProgressValue == -1 );

    p.Report(1);

    assert( GlobalProgressValue == -1 );

    p.Report(2);

    assert( GlobalProgressValue == -1 );
}

void ConstructWithNoActionWillStillRaiseProgressChangedEvent()
{
    int logged_values = -1;
    System::Progress<int> p;

    p.ProgressChanged = [&](const System::Progress<int>::ProgressEventArgs &e) { logged_values = e.data; };

    assert( logged_values == -1 );

    p.Report(0);

    assert( logged_values == 0 );

    p.Report(1);

    assert( logged_values == 1 );

    p.Report(2);

    assert( logged_values == 2 );
}

void ConstructWithActionAndProgressChangedEventWillRaiseBoth()
{
    int action_logged_values = -1;
    int event_logged_values = -1;
    System::Progress<int> p( [&](int current) { action_logged_values = current; } );

    p.ProgressChanged = [&](const System::Progress<int>::ProgressEventArgs &e) { event_logged_values = e.data; };

    assert( action_logged_values == -1 );
    assert( event_logged_values == -1 );

    p.Report(0);

    assert( action_logged_values == 0 );
    assert( event_logged_values == 0 );

    p.Report(1);

    assert( action_logged_values == 1 );
    assert( event_logged_values == 1 );

    p.Report(2);

    assert( action_logged_values == 2 );
    assert( event_logged_values == 2 );
}

void Run()
{
    ConstructWithAction();
    ConstructWithExternalFunction();
    ConstructWithLambda();
    ConstructWithNoActionCausesReportToNotReportTheAction();
    ConstructWithActionAndProgressChangedEventWillRaiseBoth();
}

}

int main(void)
{
    TestProgress::Run();
    return EXIT_SUCCESS;
}
