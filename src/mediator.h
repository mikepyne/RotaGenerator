#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "rotadata.h"
#include "volunteer.h"
#include "event.h"


namespace rg
{


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
        Events
    };

    Mediator() = default;

    /// \brief Get the number of items in a list
    /// \param[in] which Which list to count (#CountTypes)
    /// \returns the number of items from the list
    int count(
        CountTypes which
    );

    /// \brief Load data
    void loadData();

    /// \brief Get data for a volunteer
    /// \param[in] id The id of the volunteer
    /// \returns A #rg::Volunteer object
    ///
    /// Will throw Invalid if the ID doesn't exist
    Volunteer getVolunteer(
        int id
    );

    /// \brief Get data for an event
    /// \param[in] id The id of the event
    /// \returns An #rg::Event object
    ///
    /// Will throw Invalid if the ID doesn't exist
    Event getEvent(
        int id
    );

private:
    RotaData<Volunteer>     volunteers;     ///< The volunteers
    RotaData<Event>         events;         ///< The events

    /// \brief Load the data for the Volunteers list
    void loadVolunteers();

    /// \brief Load the data for the Events list
    void loadEvents();
};

}
#endif // MEDIATOR_H
