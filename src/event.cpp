#include "event.h"

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

