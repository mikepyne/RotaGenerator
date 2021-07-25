#include "mediator.h"
#include "rgexception.h"
#include "rota.h"

using nlohmann::json;

namespace rg
{
Rota::Rota(const nlohmann::json& r) :
    id(r.at("id")),
    label(r.at("label")),
    description(r.at("description"))
{
    try
    {
        events = std::vector<int>(r.at("events"));
    }
    catch (json::exception& e)
    {
        throw rg::MissingKey(id, "events");
    }
}

Rota& Rota::operator=(const Rota& r)
{
    id          = r.id;
    label       = r.label;
    description = r.description;
    events      = r.events;
    return *this;
}

Rota& Rota::operator=(const Rota&& r)
{
    id          = std::move(r.id);
    label       = std::move(r.label);
    description = std::move(r.description);
    events      = std::move(r.events);
    return *this;
}

// void Rota::generate(
//    std::shared_ptr<rg::Mediator> m,
//    date::month month,
//    int duration
//)
//{
//    for(int e : events)
//    {
//        auto event = m->getEvent(e);
//        event.get_day();
//    }
//}

void Rota::add_events(const std::vector<int>& to_add)
{
    events.insert(std::end(events), std::begin(to_add), std::end(to_add));
    std::sort(std::begin(events), std::end(events));
    auto l = std::unique(std::begin(events), std::end(events));
    events.erase(l, std::end(events));
}

void Rota::remove_events(const std::vector<int>& to_remove)
{
    auto remove_things = [&to_remove](int i) {
        auto l = std::find(std::begin(to_remove), std::end(to_remove), i);
        return l != std::end(to_remove);
    };

    auto l = std::remove_if(std::begin(events), std::end(events), remove_things);

    events.erase(l, std::end(events));
}

bool Rota::eq(const Rota& source) const
{
    return label == source.label && description == source.description
           && events == source.events;
}

}    // namespace rg
