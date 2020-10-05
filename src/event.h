#ifndef EVENT_H
#define EVENT_H

#include <string>

/// \class Event
/// \brief Describes an event that needs volunteers
///
/// An event is something that needs volunteers to help it run. It may be a
/// mass, or another regular event like cleaning.
///
/// Each event has a label, such as "Sunday Mass", or "10 am Mass"; the
/// description should give a longer description of the event. Each event also
/// indicates how many volunteers are required for the event.
class Event
{
public:
    Event() = default;

private:
    int id {0};                     ///< ID of the event
    std::string label {""};         ///< Simple label for the event
    std::string description {""};   ///< Longer description of the event
    int vols_needed {0};            ///< How many volunteers needed for the event
};

#endif // EVENT_H
