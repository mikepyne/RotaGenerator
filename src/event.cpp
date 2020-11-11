#include "event.h"

Event& Event::operator=(
    const Event& e
)
{
    id = e.id;
    label = e.label;
    description = e.description;
    vols_needed = e.vols_needed;
    return *this;
}

Event& Event::operator=(
    const Event&& e
)
{
    id = std::move(e.id);
    label = std::move(e.label);
    description = std::move(e.description);
    vols_needed = std::move(e.vols_needed);
    return *this;
}

bool Event::operator==(
    const Event& source
) const
{
    return label == source.label &&
            description == source.description &&
            vols_needed == source.vols_needed;
}

bool Event::operator!=(
    const Event &source
) const
{
    return !(*this == source);
}

void Event::to_json(
    json& j
)
{
    j = json {
        {key_id, id},
        {key_label, label},
        {key_description, description},
        {key_vols_needed, vols_needed}
    };
}

void Event::from_json(
    json &j
)
{
    id = j.at(key_id);
    label = j.at(key_label);
    description = j.at(key_description);
    vols_needed = j.at(key_vols_needed);
}

