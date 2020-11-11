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
    /// \name Constructors
    /// @{

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

    /// \brief Copy constructor
    /// \param[in] e To copy from
    Event(
        const Event& e
    ) : id(e.id),
        label(e.label),
        description(e.description),
        vols_needed(e.vols_needed) {};

    /// \brief Move constructor
    /// \param[in] e To move from
    Event(
        const Event&& e
    ) : id(std::move(e.id)),
        label(std::move(e.label)),
        description(std::move(e.description)),
        vols_needed(std::move(e.vols_needed)) {};
    ///@}

    /// \name Assignment operators
    /// @{

    /// \brief Copy assignment
    /// \param[in] e To copy from
    Event& operator=(
        const Event& e
    );

    /// \brief Move assignment
    /// \param[in] e To move from
    Event& operator=(
        const Event&& e
    );
    /// @}

    /// \brief Equality operator
    /// \param[in] source Event to compare to
    /// \return true if the label, description and number of volunteers match.
    /// The ID is not included in the comparison
    bool operator==(
        const Event& source
    ) const;

    /// \brief Inequality operator
    /// \param[in] source Event to compare to
    /// \return true if the two Events do not match
    bool operator!=(
        const Event& source
    ) const;

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

    /// \name Properties
    /// @{

    /// \brief Get the ID for this event
    /// \return the ID
    int get_id() {return id;};

    /// \brief Get the label for this event
    /// \return the label
    std::string get_label() {return label;};

    /// \brief Get the description for this event
    /// \return the description
    std::string get_description() {return description;};

    /// \brief Get the number of volunteers for this event
    /// \return the number of volunteers
    int get_vols_needed() {return vols_needed;};
    /// @}

private:
    int id {0};                     ///< ID of the event
    std::string label {""};         ///< Simple label for the event
    std::string description {""};   ///< Longer description of the event
    int vols_needed {0};            ///< How many volunteers needed for the event
};

#endif // EVENT_H
