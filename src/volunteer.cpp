#include "volunteer.h"

using nlohmann::json;

namespace rg
{
Volunteer::Volunteer(const nlohmann::json& v) :
    id(v.at("id")),
    firstName(v.at("firstName")),
    lastName(v.at("lastName")),
    phoneHome(v.at("phoneHome")),
    phoneMobile(v.at("phoneMobile")),
    email(v.at("email"))
{
}

Volunteer& Volunteer::operator=(const Volunteer& v)
{
    id          = v.id;
    firstName   = v.firstName;
    lastName    = v.lastName;
    phoneHome   = v.phoneHome;
    phoneMobile = v.phoneMobile;
    email       = v.email;
    return *this;
}

Volunteer& Volunteer::operator=(const Volunteer&& v)
{
    id          = std::move(v.id);
    firstName   = std::move(v.firstName);
    lastName    = std::move(v.lastName);
    phoneHome   = std::move(v.phoneHome);
    phoneMobile = std::move(v.phoneMobile);
    email       = std::move(v.email);
    return *this;
}

Volunteer& Volunteer::operator=(const nlohmann::json& v)
{
    id          = v.at("id");
    firstName   = v.at("firstName");
    lastName    = v.at("lastName");
    phoneHome   = v.at("phoneHome");
    phoneMobile = v.at("phoneMobile");
    email       = v.at("email");
    return *this;
}

bool Volunteer::operator==(const Volunteer& source) const
{
    return eq(source);
}

bool Volunteer::operator!=(const Volunteer& source) const
{
    return !eq(source);
}

void Volunteer::set_name(const std::string& name)
{
    auto pos = name.find(" ");
    if (pos == std::string::npos)
    {
        // No space in the name; make it all last name
        lastName = name;
    }
    else
    {
        // Before the first space is the first name, everything after is the
        // last name.
        // This is perhaps a naive approach and may not survive first contact
        // with "the enemy" (end users!).
        auto f    = name.substr(0, pos);
        auto l    = name.substr(pos + 1);
        firstName = f;
        lastName  = l;
    }
}

bool Volunteer::eq(const Volunteer& source) const
{
    return firstName == source.firstName && lastName == source.lastName
           && phoneHome == source.phoneHome && phoneMobile == source.phoneMobile
           && email == source.email;
}

}    // namespace rg
