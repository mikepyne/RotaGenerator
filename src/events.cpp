#include <fstream>
#include <nlohmann/json.hpp>

#include "events.h"

using nlohmann::json;

void Events::load(
    std::istream& in
)
{
    if (in.good())
    {
        json all;
        in >> all;
        for (auto e: all)
        {
            Event event;
            event.from_json(all);
            add(event);
        }
    }
}

void Events::save(
    std::ostream& out
)
{
    json j;
    for (auto e: events)
    {
        e.second.to_json(j);
    }
    out << j << std::endl;
}

void Events::add(
    Event event
)
{
    events.emplace(std::make_pair(event.get_id(), event));
}
