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
    /// \param[in] l Label
    /// \param[in] d Description
    /// \param[in] v Volunteers needed
    Event(
        const std::string& l,
        const std::string& d,
        int v
    ) : label(l),
        description(d),
        volsNeeded(v) {};

    /// \brief Copy constructor
    /// \param[in] e To copy from
    Event(
        const Event& e
    ) : label(e.label),
        description(e.description),
        volsNeeded(e.volsNeeded) {};

    /// \brief Move constructor
    /// \param[in] e To move from
    Event(
        const Event&& e
    ) : label(std::move(e.label)),
        description(std::move(e.description)),
        volsNeeded(std::move(e.volsNeeded)) {};
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

    /// \name Properties
    /// @{

    /// \brief Get the label for this event
    /// \return the label
    std::string get_label() const {return label;};

    /// \brief Set the label for this event
    /// \param l the new label
    void set_label(
        const std::string& l
    ) {label = l;};

    /// \brief Get the description for this event
    /// \return the description
    std::string get_description() const {return description;};

    /// \brief Set the description for this event
    /// \param d the new description
    void set_description(
        const std::string& d
    ) {description = d;};

    /// \brief Get the number of volunteers for this event
    /// \return the number of volunteers
    int get_vols_needed() const {return volsNeeded;};

    /// \brief Set the label for this event
    /// \param n the number of volunteers
    void set_vols_needed(
        const std::string& n
    ) {label = n;};

    /// @}

    /// \brief Nlohmann JSON boilerplate
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Event, label, description,
                                   volsNeeded);

private:
    std::string label {""};         ///< Simple label for the event
    std::string description {""};   ///< Longer description of the event
    int volsNeeded {0};             ///< How many volunteers needed for the event
};

#endif // EVENT_H
