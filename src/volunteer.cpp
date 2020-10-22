#include "volunteer.h"

Volunteer& Volunteer::operator=(
    const Volunteer& v
)
{
    id = v.id;
    first_name = v.first_name;
    last_name = v.last_name;
    phone_home = v.phone_home;
    phone_mobile = v.phone_mobile;
    email = v.email;
    return *this;
}

Volunteer& Volunteer::operator=(
    const Volunteer&& v
)
{
    id = std::move(v.id);
    first_name = std::move(v.first_name);
    last_name = std::move(v.last_name);
    phone_home = std::move(v.phone_home);
    phone_mobile = std::move(v.phone_mobile);
    email = std::move(v.email);
    return *this;
}

bool Volunteer::operator==(
    const Volunteer& source
) const
{
    return first_name == source.first_name &&
           last_name == source.last_name &&
           phone_home == source.phone_home &&
           phone_mobile == source.phone_mobile &&
           email == source.email;
}

bool Volunteer::operator!=(
    const Volunteer& source
) const
{
    return !(*this == source);
}

void Volunteer::to_json(json& j)
{
    j = json {
        {key_id, id},
        {key_first, first_name},
        {key_last, last_name},
        {key_home, phone_home},
        {key_mobile, phone_mobile},
        {key_email, email}
    };
}

void Volunteer::from_json(json& j)
{
    id = j.at(key_id);
    first_name = j.at(key_first);
    last_name = j.at(key_last);
    phone_home = j.at(key_home);
    phone_mobile = j.at(key_mobile);
    email = j.at(key_email);
}
