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

json Volunteer::to_json() const
{
    json j {
        {id, {
                {key_first, first_name},
                {key_last, last_name},
                {key_home, phone_home},
                {key_mobile, phone_mobile},
                {key_email, email}
            }
        }
    };
    std::string dump = j.dump();
    return j;
}

void Volunteer::from_json(const json& j)
{
    for (auto& [key, value]: j.items())
    {
        id = key;
        first_name = value.at(key_first);
        last_name = value.at(key_last);
        phone_home = value.at(key_home);
        phone_mobile = value.at(key_mobile);
        email = value.at(key_email);
    }
}
