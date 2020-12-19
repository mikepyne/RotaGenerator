#ifndef VOLUNTEER_H
#define VOLUNTEER_H

#include <string>
#include <nlohmann/json.hpp>

using nlohmann::json;

/// \class Volunteer
/// \brief Details of a volunteer
class Volunteer
{
public:
    /// \name Constructors
    ///@{

    /// \brief Default constructor
    Volunteer() = default;

    /// \brief Construct from JSON
    /// \param[in] v JSON to construct from
    Volunteer(
        const json& v
    );

    /// \brief Copy constructor
    /// \param[in] v To copy from
    Volunteer(
        const Volunteer& v
    ) : firstName(v.firstName),
        lastName(v.lastName),
        phoneHome(v.phoneHome),
        phoneMobile(v.phoneMobile),
        email(v.email) {};

    /// \brief Move constructor
    /// \param[in] v To move from
    Volunteer(
        const Volunteer&& v
    ) : firstName(std::move(v.firstName)),
        lastName(std::move(v.lastName)),
        phoneHome(std::move(v.phoneHome)),
        phoneMobile(std::move(v.phoneMobile)),
        email(std::move(v.email)) {};

    /// \brief Construct a volunteer from individual details
    /// \param[in] f First name
    /// \param[in] l Last name
    /// \param[in] h Home phone number
    /// \param[in] m Mobile phone number
    /// \param[in] e Email address
    Volunteer(
        std::string f,
        std::string l,
        std::string h,
        std::string m,
        std::string e
    ) : firstName(f),
        lastName(l),
        phoneHome(h),
        phoneMobile(m),
        email(e) {};

    /// \brief Construct a volunteer from an array of details
    /// \param details Array containing the details
    ///
    /// The array will contain five strings, ordered first name, last name, home
    /// phone, mobile phone, email
    Volunteer(
        const std::array<std::string, 5>& details
    ) : firstName(details[0]),
        lastName(details[1]),
        phoneHome(details[2]),
        phoneMobile(details[3]),
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

    /// \brief Assignment from JSON
    /// \param[in] v JSON to assign from
    Volunteer& operator=(
        const json& v
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

    /// \brief Get the first name for this volunteer
    /// \return the first name
    const std::string& get_first_name() const {return firstName;};

    /// \brief Set the first name for this volunteer
    void set_first_name(
        const std::string& fn
    ) {firstName = fn;}

    /// \brief Get the last name for this volunteer
    /// \return the second name
    const std::string& get_last_name() const {return lastName;};

    /// \brief Set the last name for this volunteer
    void set_last_name(
        const std::string& sn
    ) {lastName = sn;}

    /// \brief Get the first name for this volunteer
    /// \return the first name
    const std::string& get_phone_home() const {return phoneHome;};

    /// \brief Set the home phone for this volunteer
    void set_phone_home(
        const std::string& ph
    ) {phoneHome = ph;}

    /// \brief Get the first name for this volunteer
    /// \return the first name
    const std::string& get_phone_mobile() const {return phoneMobile;};

    /// \brief Set the mobile phone for this volunteer
    void set_phone_mobile(
        const std::string& pm
    ) {phoneMobile = pm;}

    /// \brief Get the first name for this volunteer
    /// \return the first name
    const std::string& get_email() const {return email;};

    /// \brief Set the email for this volunteer
    void set_email(
        const std::string& e
    ) {email = e;}

    ///@}

    /// \brief Nlohmann JSON boilerplate
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Volunteer, firstName, lastName,
                                   phoneHome, phoneMobile, email);

private:
    std::string firstName {""};    ///< First name
    std::string lastName {""};     ///< Last name
    std::string phoneHome {""};    ///< Home phone number
    std::string phoneMobile {""};  ///< Mobile phone number
    std::string email {""};         ///< Email address
};


#endif // VOLUNTEER_H
