#include "event.h"

Event::Event(
    const json& e
) : id(e.at("id")),
    label(e.at("label")),
    description(e.at("description")),
    volsNeeded(e["volsNeeded"].get<int>())
{
}

Event& Event::operator=(
    const Event& e
)
{
    id = e.id;
    label = e.label;
    description = e.description;
    volsNeeded = e.volsNeeded;
    return *this;
}

Event& Event::operator=(
    const Event&& e
)
{
    id = std::move(e.id);
    label = std::move(e.label);
    description = std::move(e.description);
    volsNeeded = std::move(e.volsNeeded);
    return *this;
}

bool Event::operator==(
    const Event& source
) const
{
    return eq(source);
}

bool Event::operator!=(
    const Event &source
) const
{
    return !eq(source);
}

bool Event::eq(
    const Event& source
) const
{
    return label == source.label &&
           description == source.description &&
           volsNeeded == source.volsNeeded;
}
