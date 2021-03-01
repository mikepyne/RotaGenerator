#ifndef ROTADETAILS_H
#define ROTADETAILS_H

#include <string>
#include <nlohmann/json.hpp>

using nlohmann::json;


/// \class RotaDetails
/// \brief Details for a rota
///
/// A rota contains a list of the volunteers for the rota and a list of events
/// they're needed for.
class RotaDetails
{
public:
    /// \name Constructors
    /// @{

    /// \brief Default constructor
    RotaDetails() = default;

    /// \brief Construct from JSON
    /// \param[in] j JSON to construct from
    RotaDetails(
        const json& j
    );

    /// \brief Copy constructor
    /// \param[in] rd To copy from
    RotaDetails(
        const RotaDetails& rd
    ) : id(rd.id),
        label(rd.label)
    {};

    /// \brief Move constructor
    /// \param[in] rd To move from
    RotaDetails(
        const RotaDetails&& rd
    ) : id(std::move(rd.id)),
        label(std::move(rd.label))
    {};

    /// \brief Construct RotaDetails from individual details
    /// \param[in] i ID
    /// \param[in] l Label
    RotaDetails(
        int i,
        const std::string& l
    ) : id(i),
        label(l)
    {};

    /// @}

    /// \name Operators
    /// @{

    /// \brief Copy assignment
    /// \param[in] rd RotaDetails to copy from
    RotaDetails& operator=(
        const RotaDetails& rd
    );

    /// \brief Move assignment
    /// \param[in] rd RotaDetails to move from
    RotaDetails& operator=(
        const RotaDetails&& rd
    );

    /// \brief Assignment from JSON
    /// \param[in] j JSON to assign from
    RotaDetails& operator=(
        const json& j
    );

    /// \brief Equality operator
    /// \param[in] rhs RotaDetails to compare to
    /// \returns true when all properties, except ID, match
    bool operator==(
        const RotaDetails& rhs
    ) const;

    /// \brief Inequality operator
    /// \param[in] rhs RotaDetails to compare to
    /// \returns true when all properties do no match (excluding ID)
    bool operator!=(
        const RotaDetails& rhs
    ) const;
    /// @}

    /// \name Properties
    /// @{

    /// \brief Get the ID
    /// \returns the ID
    int get_id() {return id;}

    /// \brief Set the ID
    /// \param[in] i the new ID
    void set_id(
        int i
    ) {id = i;}

    /// \brief Get the rota label
    /// \returns the rota label
    const std::string& get_label() {return label;}

    /// \brief Set the label for the rota
    /// \param[in] l the new label
    void set_label(
        const std::string& l
    ) {label = l;}

    /// @}

    /// \brief Add a volunteer
    /// \param[in] id To add
    void add_volunteer(
        int id
    );

    /// \brief Add an event
    /// \param[in] id To add
    void add_event(
        int id
    );

    /// \brief Nlohmann JSON boilerplate
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(RotaDetails, id, label);

protected:
    /// \brief Compare a RotaDetails object with this one
    /// \param[in] rhs the other RotaDetails object
    /// \returns true when the two object match
    ///
    /// Used from the equality operators (==/!=); defined separately so it can
    /// be mocked.
    /// The comparison excludes the ID.
    virtual bool eq(
        const RotaDetails& rhs
    ) const;

private:
    int         id {0};         ///< ID for the rota
    std::string label {""};     ///< Name of the rota

};

#endif // ROTADETAILS_H
