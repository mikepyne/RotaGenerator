#ifndef ROTADETAILS_H
#define ROTADETAILS_H


/// \class RotaDetails
/// \brief Details for a rota
///
/// A rota contains a list of the volunteers for the rota and a list of events
/// they're needed for.
class RotaDetails
{
public:
    RotaDetails() = default;

    /// \brief Add a volunteer
    /// \param[in] id To add
    void addVolunteer(
        int id
    );

    /// \brief Add an event
    /// \param[in] id To add
    void addEvent(
        int id
    );

private:
    int id {0};                 ///< ID for the rota
};

#endif // ROTADETAILS_H
