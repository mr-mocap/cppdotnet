#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventKeywords
{
    All  = -1, //@< All the bits are set to 1, representing every possible group of events
    None =  0, //@< No filtering on keywords is performed when the event is published
    MicrosoftTelemetry = 562949953421312,  //@< Attached to all Microsoft telemetry events
    WdiContext         = 562949953421312,  //@< Attached to all Windows Diagnostics Infrastructure (WDI) context events
    WdiDiagnostic      = 1125899906842624, //@< Attached to all Windows Diagnostics Infrastructure (WDI) diagnostic events
    Sqm	               = 2251799813685248, //@< Attached to all Service Quality Mechanism (SQM) events
    AuditFailure       = 4503599627370496, //@< Attached to all failed security audit events. Use this keyword only for events in the security log.
    CorrelationHint    = 4503599627370496, //@< Attached to transfer events where the related activity ID (correlation ID) is a computed value and is not guaranteed to be unique (that is, it is not a real GUID).
    AuditSuccess       = 9007199254740992, //@< Attached to all successful security audit events. Use this keyword only for events in the security log.
    EventLogClassic    = 36028797018963968 //@< Attached to events that are raised by using the @c RaiseEvent function 
};

}