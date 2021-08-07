#include <fstream>

#include <spdlog/spdlog.h>

#include "rgexception.h"
#include "mediator.h"

namespace rg
{
//-----------------------------------------------------------------------------
// Public Methods

int Mediator::count(CountTypes which)
{
    switch (which)
    {
        case CountTypes::Volunteers:
            return volunteers.count();
        case CountTypes::Events:
            return events.count();
        case CountTypes::Rotas:
            return rotas.count();
    }
    return -1;
}

void Mediator::loadData(std::filesystem::path data_path)
{
    loadVolunteers(data_path);
    loadEvents(data_path);
    loadRotas(data_path);
}

Volunteer Mediator::getVolunteer(int id)
{
    return volunteers.at(id);
}

void Mediator::updateVolunteer(const Volunteer& v)
{
    volunteers.update(v.get_id(), v);
    saveVolunteers(data_path);
}

Event Mediator::getEvent(int id)
{
    return events.at(id);
}

Rota Mediator::getRota(int id)
{
    return rotas.at(id);
}

//-----------------------------------------------------------------------------
// Private Methods

void Mediator::loadVolunteers(std::filesystem::path data_path)
{
    data_path /= "volunteers.json";
    std::fstream data(data_path, std::ios::in);

    if (data.good())
    {
        spdlog::debug("Opened Volunteers file");
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

void Mediator::loadEvents(std::filesystem::path data_path)
{
    data_path /= "events.json";
    std::fstream data(data_path, std::ios::in | std::ios::out | std::ios::app);

    if (data.good())
    {
        spdlog::debug("Opened Events file");
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

void Mediator::loadRotas(std::filesystem::path data_path)
{
    data_path /= "rotas.json";
    std::fstream data(data_path, std::ios::in | std::ios::out | std::ios::app);
    if (data.good())
    {
        spdlog::debug("Opened Rotas file");
        try
        {
            rotas.load(data);
        }
        catch (RGException& e)
        {
            spdlog::error("Error loading rotas: {}", e.what());
            throw e;
        }
    }
}

void Mediator::saveVolunteers(std::filesystem::path data_path)
{
    data_path /= "volunteers.json";
    std::fstream data(data_path, std::ios::out | std::ios::trunc);
    if (data.good())
    {
        spdlog::debug("Opened Volunteers file for saving");
        try
        {
            volunteers.save(data);
        }
        catch (RGException& e)
        {
            spdlog::error("Error saving volunteers: {}", e.what());
            throw e;
        }
    }
}

}    // namespace rg