#include "rgexception.h"
#include "rota.h"

using nlohmann::json;

namespace rg
{

Rota::Rota(
    const nlohmann::json& r
) : id(r.at("id")),
    label(r.at("label")),
    description(r.at("description")),
    events(r.at("events"))
{
    try
    {
        events = std::vector<int>(r.at("events"));
    }  catch (nlohmann::json::exception& e)
    {
        throw rg::MissingKey(id, "events");
    }
}

Rota& Rota::operator=(
    const Rota &r
)
{
    id = r.id;
    label = r.label;
    description = r.description;
    events = r.events;
    return *this;
}

Rota& Rota::operator=(
    const Rota&& r
)
{
    id = std::move(r.id);
    label = std::move(r.label);
    description = std::move(r.description);
    events = std::move(r.events);
    return *this;
}

void Rota::generate(
    date::year_month_day start,
    date::year_month_day end
)
{
}

bool Rota::eq(
    const Rota& source
) const
{
    return label == source.label &&
           description == source.description &&
           events == source.events;
}

}   // namespace rg
