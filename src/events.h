#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>
#include <map>

#include "event.h"

static std::string_view events_fname{"events.txt"};

/// \class Events
/// \brief Collection of Events
class Events
{
public:
    Events() = default;

    /// \brief Load events from file
    void load(
        std::istream& in
    );

    /// \brief Save events to file
    void save(
        std::ostream& out
    );

    /// \brief Add an event to the list
    void add(
        Event event
    );

private:
    std::map<int, Event> events;  ///< The events
};

#endif // EVENTS_H
