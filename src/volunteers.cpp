#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include "volunteers.h"

using nlohmann::json;

void Volunteers::load(
    std::istream& in
)
{
    in.peek();
    if (in.good() && !in.eof())
    {
        json all;
        in >> all;
        for (auto& [k, v]: all.items())
        {
            std::cout << v.dump(4) << std::endl;
            Volunteer vol;
            volunteers.emplace(std::make_pair(k, v));
        }
    }
}

void Volunteers::save(
    std::ostream& out
)
{
    json j = volunteers;
    out << j << std::endl;
    out.flush();
}

bool Volunteers::add(
    Volunteer vol
)
{
    for (auto& [k, v]: volunteers)
    {
        if (v == vol)
        {
            return false;
        }
    }
    auto id = 1;
    std::string new_key {std::to_string(id)};
    if (volunteers.size() > 0)
    {
        auto last_key = volunteers.crbegin()->first;
        id = std::stoi(last_key) + 1;
        new_key = std::to_string(id);
    }
    if (volunteers.count(new_key) == 0)
    {
        volunteers.emplace(std::make_pair(new_key, vol));
    }
    return true;
}
