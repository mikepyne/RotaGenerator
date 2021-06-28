#ifndef ROTA_H
#define ROTA_H

#include <string>
#include <vector>

#include <nlohmann/json.hpp>
#include <date/date.h>


namespace rg
{

/// \class Rota
/// \brief Create a rota
class Rota
{
public:
    /// \name Constructors
    /// @{

    /// \brief Default constructor
    Rota() = default;

    /// \brief Construct from JSON
    /// \param[in] r JSON to construct from
    Rota(
        const nlohmann::json& r
    );

    /// \brief Copy constructor
    /// \param[in] r To copy from
    Rota(
        const Rota& r
    ) : id(r.id),
        label(r.label),
        description(r.description),
        events(r.events) {};

    /// \brief Move constructor
    /// \param[in] r To move from
    Rota(
        const Rota&& r
    ) : id(std::move(r.id)),
        label(std::move(r.label)),
        description(std::move(r.description)),
        events(std::move(r.events)) {};

    /// \brief Construct a rota from individual details
    /// \param[in] i ID
    /// \param[in] l Label
    /// \param[in] d Description
    /// \param[in] e Events
    Rota(
        int i,
        const std::string& l,
        const std::string& d,
        const std::vector<int>& e
    ) : id(i),
        label(l),
        description(d),
        events(e) {};

    /// @}

    /// \name Operators
    /// @{

    /// \brief Copy assignment
    /// \param[in] r Rota to copy from
    Rota& operator=(
        const Rota& r
    );

    /// \brief Move assignment
    /// \param[in] r Rota to move from
    Rota& operator=(
        const Rota&& r
    );

    /// \brief Equality operator
    /// \param[in] source Rota to compare to
    /// \return true if the label, description, and list of events match.
    ///
    /// The ID is not included in the comparison
    bool operator==(
        const Rota& source
    ) const {return eq(source);}

    /// \brief Inequality operator
    /// \param[in] source Rota to compare to
    /// \return true if the two Rotas don't match
    bool operator!=(
        const Rota& source
    ) const {return !eq(source);}

    /// @}

    /// @{
    /// \name Properties

    /// \brief Get the ID for this rota
    /// \return the ID
    virtual int get_id() const {return id;};

    /// \brief Set the ID for the rota
    /// \param[in] i The new ID
    virtual void set_id(
        int i
    ) {id = i;}

    /// \brief Get the label for this rota
    /// \return the label
    std::string get_label() const {return label;}

    /// \brief Set the label for this event
    /// \param l the new label
    void set_label(
        const std::string& l
    ) {label = l;}

    /// \brief Get the description for this rota
    /// \return the description
    std::string get_description() const {return description;}

    /// \brief Set the description for this rota
    /// \param d the new description
    void set_description(
        const std::string& d
    ) {description = d;}

    /// @}

//    /// \brief Generate the rota
//    /// \param[in] m Mediator.
//    /// \param[in] start Starting month of the rota
//    /// \param[in] duration Number of months the rota is for
//    void generate(
//        std::shared_ptr<rg::Mediator> m,
//        date::month start,
//        int duration
//    );

    /// \brief Nlohmann JSON boilerplate
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Rota, id, label, description, events);

protected:
    /// \brief Compare another Rota with this one
    /// \param[in] rhs The other Rota
    /// \return true if the two Rotas match
    ///
    /// Compares the label, description, and list of events. The ID is not
    /// included.
    virtual bool eq(
        const Rota& rhs
    ) const;

private:
    int                             id {0};             ///< Rota ID
    std::string                     label {""};         ///< Label for the rota
    std::string                     description {""};   ///< Longer description
    std::vector<int>                events;             ///< Events in the rota
};

}   // namespace rg
#endif // ROTA_H
