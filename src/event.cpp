#include <date/date.h>

#include "rgexception.h"
#include "event.h"

Event::Event(
    const json& e
) : id(e.at("id")),
    label(e.at("label")),
    description(e.at("description")),
    volsNeeded(e["volsNeeded"].get<int>())
{
    try
    {
        volunteers = std::vector<int>(e.at("volunteers"));
    }
    catch (nlohmann::json::exception& ex)
    {
        throw RGException(RGException::errors::missing_key, -1, -1, "volunteers");
    }
    try
    {
        day = e.at("day").get<uint8_t>();
    }
    catch (nlohmann::json::exception& ex)
    {
        // Events don't have to have a specific day, so a missing day key
        // isn't an error.
        day = 8;
    }
}

Event& Event::operator=(
    const Event& e
)
{
    id = e.id;
    label = e.label;
    description = e.description;
    volsNeeded = e.volsNeeded;
    volunteers = e.volunteers;
    day = e.day;
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
    volunteers = std::move(e.volunteers);
    day = std::move(e.day);
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
           volsNeeded == source.volsNeeded &&
           volunteers == source.volunteers &&
           day == source.day;
}

std::string Event::day_to_string(
    uint8_t day
)
{
    date::weekday wd(day);
    std::stringstream out;
    date::to_stream(out, "%A", wd);
    return out.str();
}

void Event::add_volunteers(
    const std::vector<int> &to_add
)
{
    volunteers.insert(std::end(volunteers), std::begin(to_add), std::end(to_add));
    std::sort(std::begin(volunteers), std::end(volunteers));
    auto l = std::unique(std::begin(volunteers), std::end(volunteers));
    volunteers.erase(l, std::end(volunteers));
}

void Event::remove_volunteers(
    const std::vector<int> &to_remove
)
{
    auto remove_things = [&to_remove](int i){
        auto l = std::find(std::begin(to_remove), std::end(to_remove), i);
        return l != std::end(to_remove);
    };

    auto l = std::remove_if(std::begin(volunteers), std::end(volunteers),
                            remove_things);

    volunteers.erase(l, std::end(volunteers));

}
