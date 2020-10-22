#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <nlohmann/json.hpp>

using nlohmann::json;

constexpr auto key_id {"id"};
constexpr auto key_label {"label"};
constexpr auto key_description {"description"};
constexpr auto key_vols_needed {"volsNeeded"};

/// \class Event
/// \brief Describes an event that needs volunteers
///
/// An event is something that needs volunteers to help it run. It may be a
/// mass, or another regular event like cleaning.
///
/// Each event has a label, such as "Sunday Mass", or "10 am Mass"; the
/// description should give a longer description of the event. Each event also
/// indicates how many volunteers are required for the event.
class Event
{
public:
    /// \brief Default constructor
    Event() = default;

    /// \brief Constructor
    /// \param[in] i ID
    /// \param[in] l Label
    /// \param[in] d Description
    /// \param[in] v Volunteers needed
    Event(
        int i,
        std::string l,
        std::string d,
        int v
    ) : id(i),
        label(l),
        description(d),
        vols_needed(v) {};

    /// \brief Serialise to JSON
    /// \param[out] j json object to write to
    void to_json(
        json& j
    );

    /// \brief De-serialise from JSON
    /// \param[in] j json object to read from
    void from_json(
        json& j
    );

private:
    int id {0};                     ///< ID of the event
    std::string label {""};         ///< Simple label for the event
    std::string description {""};   ///< Longer description of the event
    int vols_needed {0};            ///< How many volunteers needed for the event
};

#endif // EVENT_H
