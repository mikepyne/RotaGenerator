#ifndef EVENTS_H
#define EVENTS_H

#include "rotadata.h"

#include "event.h"

static std::string_view events_fname {"events.txt"};

/// \class Events
/// \brief Collection of Events
class Events : public RotaData<Event>
{
public:
    Events() = default;
};

#endif // EVENTS_H
