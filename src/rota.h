#ifndef ROTA_H
#define ROTA_H

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using nlohmann::json;

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
        const json& r
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

    /// \brief Generate the rota
    void generate();

    /// \brief Nlohmann JSON boilerplate
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Rota, id, label, description, events);

private:
    int                 id {0};             ///< Rota ID
    std::string         label {""};         ///< Label for the rota
    std::string         description {""};   ///< Longer description
    std::vector<int>    events {};          ///< Events in the rota
};

#endif // ROTA_H
