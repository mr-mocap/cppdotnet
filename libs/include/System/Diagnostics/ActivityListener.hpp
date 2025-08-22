#include "System/Diagnostics/Activity.hpp"
#include "System/Diagnostics/SampleActivity.hpp"
#include "System/Action.hpp"
#include "System/Func.hpp"


namespace System::Diagnostics
{

class ActivityListener final
{
public:
    ActivityListener();

    const Action<Diagnostics::Activity> &ActivityStarted() const { return _activity_started; }
                                   void  ActivityStarted(Action<Diagnostics::Activity> &callback) { _activity_started = callback; }

    const Action<Diagnostics::Activity> &ActivityStopped() const { return _activity_stopped; }
                                   void  ActivityStopped(Action<Diagnostics::Activity> &callback) { _activity_stopped = callback; }

#if 0
    ExceptionRecorder &ExceptionRecorder() { return _exception_recorder; }
#endif
    const SampleActivity<ActivityContext> &Sample() const { return _sample; }
                                     void  Sample(SampleActivity<ActivityContext> &s) { _sample = s; }

    const SampleActivity<std::string> &SampleUsingParentId() const { return _sample_using_parent_id; }
                                 void  SampleUsingParentId(SampleActivity<std::string> &callback) const { return _sample_using_parent_id = callback; }

    const Func<ActivitySource, bool> &ShouldListenTo() const { return _should_listen_to; }
                                void  ShouldListenTo(Func<ActivitySource, bool> &func) const { _should_listen_to = func; }
protected:
    Action<Diagnostics::Activity> _activity_started;
    Action<Diagnostics::Activity> _activity_stopped;
    SampleActivity<Diagnostics::ActivityContext> _sample;
    SampleActivity<std::string>   _sample_using_parent_id;
    Func<ActivitySource, bool>    _should_listen_to;
};

}