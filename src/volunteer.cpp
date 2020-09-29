#include "volunteer.h"

Volunteer::Volunteer(
    const std::array<std::string, 5>& detail
)
{
    first_name = detail[0];
    last_name = detail[1];
    phone_home = detail[2];
    phone_mobile = detail[3];
    email = detail[4];
}

Volunteer& Volunteer::operator=(
    const Volunteer& v
)
{
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
    first_name = std::move(v.first_name);
    last_name = std::move(v.last_name);
    phone_home = std::move(v.phone_home);
    phone_mobile = std::move(v.phone_mobile);
    email = std::move(v.email);
    return *this;
}

bool Volunteer::operator==(
    const Volunteer& source
)
{
    return first_name == source.first_name &&
           last_name == source.last_name &&
           phone_home == source.phone_home &&
           phone_mobile == source.phone_mobile &&
           email == source.email;
}

void Volunteer::to_json(json& j)
{
    j = json {{"First Name", first_name},
              {"Last Name", last_name},
              {"Home Phone", phone_home},
              {"Mobile Phone", phone_mobile},
              {"Email", email}};
}

void Volunteer::from_json(json& j)
{
    first_name = j.at("First Name");
    last_name = j.at("Last Name");
    phone_home = j.at("Home Phone");
    phone_mobile = j.at("Mobile Phone");
    email = j.at("Email");
}
