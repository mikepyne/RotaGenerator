#include "rgexception.h"
#include "rota.h"

Rota::Rota(
    const json& r
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
        throw RGException(RGException::errors::invalid, -1, -1);
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

void Rota::generate()
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
