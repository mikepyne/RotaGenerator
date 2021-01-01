#include "event.h"

Event& Event::operator=(
    const Event& e
)
{
    label = e.label;
    description = e.description;
    volsNeeded = e.volsNeeded;
    return *this;
}

Event& Event::operator=(
    const Event&& e
)
{
    label = std::move(e.label);
    description = std::move(e.description);
    volsNeeded = std::move(e.volsNeeded);
    return *this;
}

bool Event::operator==(
    const Event& source
) const
{
    return label == source.label &&
           description == source.description &&
           volsNeeded == source.volsNeeded;
}

bool Event::operator!=(
    const Event &source
) const
{
    return !(*this == source);
}
