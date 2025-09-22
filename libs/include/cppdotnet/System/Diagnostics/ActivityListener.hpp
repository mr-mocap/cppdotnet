#pragma once

#include <cppdotnet/System/Diagnostics/Activity.hpp>
#include <cppdotnet/System/Diagnostics/ActivitySource.hpp>
#include <cppdotnet/System/Diagnostics/SampleActivity.hpp>
#include <cppdotnet/System/Diagnostics/ExceptionRecorder.hpp>
#include <cppdotnet/System/Action.hpp>
#include <cppdotnet/System/Func.hpp>
#include <string>


namespace System::Diagnostics
{

class ActivityListener final
{
public:
    ActivityListener() = default;
    ActivityListener(const ActivityListener &) = default;
    ActivityListener(ActivityListener &&) = default;
   ~ActivityListener()
    {
        Dispose();
    }

    ActivityListener &operator =(const ActivityListener &) = default;
    ActivityListener &operator =(ActivityListener &&) = default;

    const Action<Diagnostics::Activity> &ActivityStarted() const { return _activity_started; }
                                   void  ActivityStarted(Action<Diagnostics::Activity> &callback) { _activity_started = callback; }

    const Action<Diagnostics::Activity> &ActivityStopped() const { return _activity_stopped; }
                                   void  ActivityStopped(Action<Diagnostics::Activity> &callback) { _activity_stopped = callback; }

    const struct ExceptionRecorder &ExceptionRecorder() { return _exception_recorder; }
                               void ExceptionRecorder(struct ExceptionRecorder new_value) { _exception_recorder = new_value; }

    const SampleActivity<ActivityContext> &Sample() const { return _sample; }
                                     void  Sample(const SampleActivity<ActivityContext> &s) { _sample = s; }

    const SampleActivity<std::string> &SampleUsingParentId() const { return _sample_using_parent_id; }
                                 void  SampleUsingParentId(const SampleActivity<std::string> &callback) { _sample_using_parent_id = callback; }

    const Func<const ActivitySource &, bool> &ShouldListenTo() const { return _should_listen_to; }
                                        void  ShouldListenTo(const Func<const ActivitySource &, bool> &func) { _should_listen_to = func; }

    void Dispose();
protected:
    Action<Diagnostics::Activity> _activity_started;
    Action<Diagnostics::Activity> _activity_stopped;
    SampleActivity<Diagnostics::ActivityContext> _sample;
    SampleActivity<std::string>   _sample_using_parent_id;
    Func<const ActivitySource &, bool>  _should_listen_to;
    struct ExceptionRecorder      _exception_recorder;
};

}