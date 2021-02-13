#include "rotadetails.h"

RotaDetails::RotaDetails(
    const json& j
) : id(j.at("id")),
    label(j.at("label"))
{
}

RotaDetails& RotaDetails::operator=(
    const RotaDetails& rhs
)
{
    id = rhs.id;
    label = rhs.label;
    return *this;
}

RotaDetails& RotaDetails::operator=(
    const RotaDetails&& rhs
)
{
    id = std::move(rhs.id);
    label = std::move(rhs.label);
    return *this;
}

RotaDetails& RotaDetails::operator=(
    const json& j
)
{
    id = j.at("id");
    label = j.at("label");
    return *this;
}

bool RotaDetails::operator==(
    const RotaDetails& rhs
) const
{
    return eq(rhs);
}

bool RotaDetails::operator!=(
    const RotaDetails& rhs
) const
{
    return !eq(rhs);
}

void addVolunteer(
    int //id
)
{
}

void addEvent(
    int //id
)
{

}

bool RotaDetails::eq(
    const RotaDetails& rhs
) const
{
    return label == rhs.label;
}
