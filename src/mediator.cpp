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

void Mediator::loadData(std::filesystem::path dp)
{
    data_path = dp;
    loadVolunteers();
    loadEvents();
    loadRotas();
}

Volunteer Mediator::getVolunteer(int id)
{
    return volunteers.at(id);
}

void Mediator::updateVolunteer(const Volunteer& v)
{
    volunteers.update(v.get_id(), v);
    saveVolunteers();
}

Event Mediator::getEvent(int id)
{
    return events.at(id);
}

void Mediator::updateEvent(const Event& e)
{
    events.update(e.get_id(), e);
    saveEvents();
}

Rota Mediator::getRota(int id)
{
    return rotas.at(id);
}

void Mediator::updateRota(const Rota& r)
{
    rotas.update(r.get_id(), r);
    saveRotas();
}

//-----------------------------------------------------------------------------
// Private Methods

void Mediator::loadVolunteers()
{
    std::fstream data(data_path / vols_fname, std::ios::in);

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

void Mediator::loadEvents()
{
    std::fstream data(data_path / events_fname,
                      std::ios::in | std::ios::out | std::ios::app);

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

void Mediator::loadRotas()
{
    std::fstream data(data_path / rotas_fname,
                      std::ios::in | std::ios::out | std::ios::app);
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

void Mediator::saveVolunteers()
{
    std::fstream data(data_path / vols_fname, std::ios::out | std::ios::trunc);
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

void Mediator::saveRotas()
{
    std::fstream data(data_path / rotas_fname, std::ios::out | std::ios::trunc);
    if (data.good())
    {
        spdlog::debug("Opened rotas file for saving");
        try
        {
            rotas.save(data);
        }
        catch (RGException& e)
        {
            spdlog::error("Error saving Rotas: {}", e.what());
        }
    }
}

void Mediator::saveEvents()
{
    std::fstream data(data_path / events_fname, std::ios::out | std::ios::trunc);
    if (data.good())
    {
        spdlog::debug("Opened events file for saving");
        try
        {
            events.save(data);
        }
        catch (RGException& e)
        {
            spdlog::error("Error saving Events: {}", e.what());
        }
    }
}

}    // namespace rg
