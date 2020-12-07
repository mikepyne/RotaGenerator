#include "volunteer.h"


Volunteer& Volunteer::operator=(
    const Volunteer& v
)
{
    firstName = v.firstName;
    lastName = v.lastName;
    phoneHome = v.phoneHome;
    phoneMobile = v.phoneMobile;
    email = v.email;
    return *this;
}

Volunteer& Volunteer::operator=(
    const Volunteer&& v
)
{
    firstName = std::move(v.firstName);
    lastName = std::move(v.lastName);
    phoneHome = std::move(v.phoneHome);
    phoneMobile = std::move(v.phoneMobile);
    email = std::move(v.email);
    return *this;
}

bool Volunteer::operator==(
    const Volunteer& source
) const
{
    return firstName == source.firstName &&
           lastName == source.lastName &&
           phoneHome == source.phoneHome &&
           phoneMobile == source.phoneMobile &&
           email == source.email;
}

bool Volunteer::operator!=(
    const Volunteer& source
) const
{
    return !(*this == source);
}
