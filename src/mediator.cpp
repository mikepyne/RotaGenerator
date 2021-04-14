#include <filesystem>
#include <fstream>

#include <spdlog/spdlog.h>

#include "rgexception.h"
#include "mediator.h"

namespace rg
{

//-----------------------------------------------------------------------------
// Public Methods

int Mediator::count(
    CountTypes which
)
{
    switch (which)
    {
        case CountTypes::Volunteers:
            return volunteers.count();
        case CountTypes::Events:
            return events.count();
    }
    return -1;
}

void Mediator::loadData()
{
    loadVolunteers();
    loadEvents();
}

Volunteer Mediator::getVolunteer(
    int id
)
{
    return volunteers.at(id);
}

Event Mediator::getEvent(
    int id
)
{
    return events.at(id);
}

//-----------------------------------------------------------------------------
// Private Methods

void Mediator::loadVolunteers()
{
    std::filesystem::path p = "/home/mike/Projects/RotaGenerator/data/volunteers.txt";
    std::fstream data(p, std::ios::in | std::ios::out | std::ios::app);

    if (data.good())
    {
        spdlog::debug("Opened file");
        try
        {
            volunteers.load(data);
        }
        catch (RGException& e)
        {
            spdlog::error("Error loading volunteers: {}", e.what());
            throw std::runtime_error("Error loading Volunteers data");
        }
    }
}

void Mediator::loadEvents()
{
    std::filesystem::path p = "/home/mike/Projects/RotaGenerator/data/events.txt";
    std::fstream data(p, std::ios::in | std::ios::out | std::ios::app);

    if (data.good())
    {
        spdlog::debug("Opened file");
        try
        {
            events.load(data);
        }
        catch (RGException& e)
        {
            spdlog::error("Error loading events: {}", e.what());
            throw std::runtime_error("Error loading events data");
        }
    }
}

}   // namespace rg
