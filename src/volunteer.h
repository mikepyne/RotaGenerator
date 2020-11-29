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
        std::string i,
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

    /// \brief Construct a volunteer from an array of details
    /// \param details Array containing the details
    ///
    /// The array will contain five strings, ordered first name, last name, home
    /// phone, mobile phone, email
    Volunteer(
        const std::array<std::string, 5>& details
    ) : first_name(details[0]),
        last_name(details[1]),
        phone_home(details[2]),
        phone_mobile(details[3]),
        email(details[4]) {};
    ///@}

    ~Volunteer() = default;

    /// \name Operators
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
    /// @}

    /// \name Properties
    /// @{

    /// \brief Get the ID for this volunteer
    /// \return the ID
    const std::string& get_id() const {return id;};

    /// \brief Set the ID for this volunteer
    void set_id(
        int i
    ) {id = i;}

    /// \brief Get the first name for this volunteer
    /// \return the first name
    const std::string& get_first_name() const {return first_name;};

    /// \brief Set the first name for this volunteer
    void set_first_name(
        const std::string& fn
    ) {first_name = fn;}

    /// \brief Get the last name for this volunteer
    /// \return the second name
    const std::string& get_last_name() const {return last_name;};

    /// \brief Set the last name for this volunteer
    void set_last_name(
        const std::string& sn
    ) {last_name = sn;}

    /// \brief Get the first name for this volunteer
    /// \return the first name
    const std::string& get_phone_home() const {return phone_home;};

    /// \brief Set the home phone for this volunteer
    void set_phone_home(
        const std::string& ph
    ) {phone_home = ph;}

    /// \brief Get the first name for this volunteer
    /// \return the first name
    const std::string& get_phone_mobile() const {return phone_mobile;};

    /// \brief Set the mobile phone for this volunteer
    void set_phone_mobile(
        const std::string& pm
    ) {phone_mobile = pm;}

    /// \brief Get the first name for this volunteer
    /// \return the first name
    const std::string& get_email() const {return email;};

    /// \brief Set the email for this volunteer
    void set_email(
        const std::string& e
    ) {email = e;}

    ///@}

    /// \brief Serialise to JSON
    json to_json() const;

    /// \brief De-serialise from JSON
    /// \param[in] j to read from
    void from_json(
        const json& j
    );

private:
    std::string id {""};            ///< Volunteer ID
    std::string first_name {""};    ///< First name
    std::string last_name {""};     ///< Last name
    std::string phone_home {""};    ///< Home phone number
    std::string phone_mobile {""};  ///< Mobile phone number
    std::string email {""};         ///< Email address
};

#endif // VOLUNTEER_H
