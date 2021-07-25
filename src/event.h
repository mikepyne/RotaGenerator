#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace rg
{
/// \class Event
/// \brief Describes an event that needs volunteers
///
/// An event is something that needs volunteers to help it run. It may be a
/// mass, or another regular event like cleaning.
///
/// Each event has a label, such as "Sunday Mass", or "10 am Mass"; the
/// description should give a longer description of the event (e.g. "Sunday Mass
/// (10am)"). The number of volunteers needed for each event (that is, every
/// time the event happens, 'n' volunteers are required, not the total number
/// of volunteers available).
///
/// Each event also has a list of the volunteers who have volunteered for this
/// event (this time, all volunteers assigned, not just those for a single
/// occasion).
class Event
{
public:
    /// \name Constructors
    /// @{

    /// \brief Default constructor
    Event() = default;

    /// \brief Construct from JSON
    /// \param[in] e JSON to construct from
    Event(const nlohmann::json& e);

    /// \brief Constructor
    /// \param[in] id ID of the event
    /// \param[in] l Label
    /// \param[in] d Description
    /// \param[in] v Volunteers needed
    /// \param[in] vols Volunteers for the event
    /// \param[in] a Which day the event is on
    Event(int                    id,
          const std::string&     l,
          const std::string&     d,
          int                    v,
          const std::vector<int> vols,
          int                    a = 8) :
        id(id),
        label(l),
        description(d),
        volsNeeded(v),
        volunteers(vols),
        day(a) {};

    /// \brief Copy constructor
    /// \param[in] e To copy from
    Event(const Event& e) :
        id(e.id),
        label(e.label),
        description(e.description),
        volsNeeded(e.volsNeeded),
        volunteers(e.volunteers),
        day(e.day) {};

    /// \brief Move constructor
    /// \param[in] e To move from
    Event(const Event&& e) :
        id(std::move(e.id)),
        label(std::move(e.label)),
        description(std::move(e.description)),
        volsNeeded(std::move(e.volsNeeded)),
        volunteers(std::move(e.volunteers)),
        day(std::move(e.day)) {};
    ///@}

    /// \name Assignment operators
    /// @{

    /// \brief Copy assignment
    /// \param[in] e To copy from
    Event& operator=(const Event& e);

    /// \brief Move assignment
    /// \param[in] e To move from
    Event& operator=(const Event&& e);
    /// @}

    /// \brief Equality operator
    /// \param[in] source Event to compare to
    /// \return true if the label, description and number of volunteers match.
    /// The ID is not included in the comparison
    bool operator==(const Event& source) const;

    /// \brief Inequality operator
    /// \param[in] source Event to compare to
    /// \return true if the two Events do not match
    bool operator!=(const Event& source) const;

    /// \name Properties
    /// @{

    /// \brief Get the ID for this event
    virtual int get_id() const { return id; };

    /// \brief Set the ID for this events
    /// \param[in] i The new ID
    void set_id(int i) { id = i; }

    /// \brief Get the label for this event
    /// \return the label
    std::string get_label() const { return label; };

    /// \brief Set the label for this event
    /// \param l the new label
    void set_label(const std::string& l) { label = l; };

    /// \brief Get the description for this event
    /// \return the description
    std::string get_description() const { return description; };

    /// \brief Set the description for this event
    /// \param d the new description
    void set_description(const std::string& d) { description = d; };

    /// \brief Get the number of volunteers for this event
    /// \return the number of volunteers
    int get_vols_needed() const { return volsNeeded; };

    /// \brief Set the label for this event
    /// \param n the number of volunteers
    void set_vols_needed(const std::string& n) { label = n; };

    /// \brief Get the volunteers for the event
    /// \return the list of IDs of volunteers for the event
    std::vector<int>& get_volunteers() { return volunteers; }

    /// \brief Set the volunteers for the event
    /// \param[in] vols The new list of volunteers
    ///
    /// Calling this method **replaces** the existing list of volunteers.
    void set_volunteers(const std::vector<int>& vols) { volunteers = vols; }

    /// \brief Get the day for this event
    /// \return the day
    ///
    /// The day will be 0 - 6, where Sunday is 0, and 6 is Saturday. Sunday may
    /// also be 7. Any other value means the event doesn't have a specific day.
    uint8_t get_day() const { return day; }

    /// \brief Set the day for this event
    /// \param[in] d The new day for the event
    ///
    /// The day should be a value of 0 - 6, where 0 is Sunday and 6 is Saturday.
    /// (Sunday may also be 7). Set the day to 8 to indicate the event doesn't
    /// have a specific day.
    void set_day(uint8_t d) { day = d; }
    /// @}

    /// \brief Get a string for a given day
    /// \param[in] day To turn into a string
    /// \return a string for the day
    ///
    /// day must be between 0 (for Sunday) and 6 (Saturday); Sunday may also be
    /// 7. Values of 8 or above will result in an empty string
    static std::string day_to_string(uint8_t day);

    /// \brief Nlohmann JSON boilerplate
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Event,
                                   id,
                                   label,
                                   description,
                                   volsNeeded,
                                   volunteers,
                                   day);

    /// \brief Add volunteers to the list of volunteers for this event
    /// \param[in] to_add Volunteers to be added
    ///
    /// Merges vols into the volunteers and removes duplicates. Results in
    /// volunteers being sorted.
    void add_volunteers(const std::vector<int>& to_add);

    /// \brief Remove volunteers from the list for this event
    /// \param[in] to_remove Volunteers to be removed
    void remove_volunteers(const std::vector<int>& to_remove);

protected:
    /// \brief Compare another event with this one
    /// \param rhs the other Event
    /// \return true if the two Event objects match
    ///
    /// Used from the equality operators; defined separately so it can be
    /// mocked.
    virtual bool eq(const Event& rhs) const;

private:
    int              id {0};              ///< Event ID
    std::string      label {""};          ///< Simple label for the event
    std::string      description {""};    ///< Longer description of the event
    int              volsNeeded {0};      ///< How many required for each event
    std::vector<int> volunteers;          ///< Volunteers for this event
    uint8_t          day {8};             ///< Day of the event
};

}    // namespace rg
#endif    // EVENT_H
