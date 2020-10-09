#ifndef VOLUNTEER_H
#define VOLUNTEER_H

#include <string>
#include <nlohmann/json.hpp>

using nlohmann::json;

constexpr auto key_id {"id"};
constexpr auto key_first {"firstName"};
constexpr auto key_last {"lastName"};
constexpr auto key_home {"homePhone"};
constexpr auto key_mobile {"mobilePhone"};
constexpr auto key_email {"email"};

/// \class Volunteer
/// \brief Details of a volunteer
class Volunteer
{
public:
    /// \name Constructors
    ///@{

    /// \brief Default constructor
    Volunteer() = default;

    /// \brief Copy constructor
    /// \param[in] v To copy from
    Volunteer(
        const Volunteer& v
    ) : id(v.id),
        first_name(v.first_name),
        last_name(v.last_name),
        phone_home(v.phone_home),
        phone_mobile(v.phone_mobile),
        email(v.email) {};

    /// \brief Move constructor
    /// \param[in] v To move from
    Volunteer(
        const Volunteer&& v
    ) : id(std::move(v.id)),
        first_name(std::move(v.first_name)),
        last_name(std::move(v.last_name)),
        phone_home(std::move(v.phone_home)),
        phone_mobile(std::move(v.phone_mobile)),
        email(std::move(v.email)) {};

    /// \brief Construct a volunteer from individual details
    /// \param[in] i ID
    /// \param[in] f First name
    /// \param[in] l Last name
    /// \param[in] h Home phone number
    /// \param[in] m Mobile phone number
    /// \param[in] e Email address
    Volunteer(
        int i,
        std::string f,
        std::string l,
        std::string h,
        std::string m,
        std::string e
    ) : id(i),
        first_name(f),
        last_name(l),
        phone_home(h),
        phone_mobile(m),
        email(e) {};
    ///@}

    ~Volunteer() = default;

    /// \name Assignment Operators
    /// @{

    /// \brief Copy assignment
    /// \param[in] v Volunteer to copy from
    Volunteer& operator=(
        const Volunteer& v
    );

    /// \brief Move assignment
    /// \param[in] v Volunteer to move from
    Volunteer& operator=(
        const Volunteer&& v
    );
    /// @}

    /// \brief Comparison operator
    /// \param[in] source Volunteer to compare to
    /// \return true if the name, phone numbers and email match the source. ID
    /// is not included in the comparison.
    bool operator==(
        const Volunteer& source
    ) const;

    /// \brief Inequality operator
    /// \param[in] source Volunteer to compare with
    /// \return true if the two Volunteers do not match
    bool operator!=(
        const Volunteer& source
    ) const;

    /// \brief Serialise to JSON
    /// \param[out] j json to write to
    void to_json(
        json& j
    );

    /// \brief De-serialise from JSON
    /// \param[in] j to read from
    void from_json(
        json& j
    );

private:
    int id {0};                     ///< Volunteer ID
    std::string first_name {""};    ///< First name
    std::string last_name {""};     ///< Last name
    std::string phone_home {""};    ///< Home phone number
    std::string phone_mobile {""};  ///< Mobile phone number
    std::string email {""};         ///< Email address
};

#endif // VOLUNTEER_H
