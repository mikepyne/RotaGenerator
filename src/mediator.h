#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <filesystem>

#include "rotadata.h"
#include "volunteer.h"
#include "event.h"
#include "rota.h"

namespace rg
{
/// \name Filenames
/// \brief Constants for the filenames.
/// @{
constexpr std::string_view vols_fname {"volunteers.json"};
constexpr std::string_view events_fname {"events.json"};
constexpr std::string_view rotas_fname {"rotas.json"};
/// @}

/// \class Mediator
/// \brief Mediator to manage getting and using events and volunteers.
///
/// TODO: Pass in the data file location
class Mediator
{
public:
    /// \brief Used to determine which type to get a count for
    enum class CountTypes : int8_t
    {
        Volunteers,
        Events,
        Rotas,
    };

    Mediator() = default;

    /// \brief Get the number of items in a list
    /// \param[in] which Which list to count (#CountTypes)
    /// \returns the number of items from the list
    int count(CountTypes which);

    /// \brief Load data
    void loadData(std::filesystem::path dp);

    /// \brief Get data for a volunteer
    /// \param[in] id The id of the volunteer
    /// \returns A #rg::Volunteer object
    ///
    /// Will throw Invalid if the ID doesn't exist
    Volunteer getVolunteer(int id);

    /// \brief Update a volunteer
    /// \param[in] v The updated volunteer
    ///
    /// Replace the volunteer in the list with this one.
    void updateVolunteer(const Volunteer& v);

    /// \brief Get data for an event
    /// \param[in] id The id of the event
    /// \returns An #rg::Event object
    ///
    /// Will throw Invalid if the ID doesn't exist
    Event getEvent(int id);

    /// \brief Update an event
    /// \param[in] e The updated event
    ///
    /// Replace the event in the list with this one.
    void updateEvent(const Event& e);

    /// \brief Get data for a rota
    /// \param[in] id The id of the rota
    /// \returns A #rg::Rota object
    Rota getRota(int id);

    /// \brief Update a rota
    /// \param[in] r The updated rota
    ///
    /// Replace the volunteer in the list with this one
    void updateRota(const Rota& r);

private:
    std::filesystem::path data_path;     ///< Where the data is saved
    RotaData<Volunteer>   volunteers;    ///< The volunteers
    RotaData<Event>       events;        ///< The events
    RotaData<Rota>        rotas;         ///< The rotas

    /// \brief Load the data for the Volunteers list
    void loadVolunteers();

    /// \brief Load the data for the Events list
    void loadEvents();

    /// \brief Load the Rotas data
    void loadRotas();

    /// \brief Save Volunteers data to file.
    void saveVolunteers();

    /// \brief Save Rotas data to file.
    void saveRotas();

    /// \brief Save Events data to file
    void saveEvents();
};

}    // namespace rg
#endif    // MEDIATOR_H
