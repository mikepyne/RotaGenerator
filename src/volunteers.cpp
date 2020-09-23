#include "volunteers.h"

#include <fstream>
#include <nlohmann/json.hpp>

using nlohmann::json;

void Volunteers::load(
    std::filesystem::path path
)
{
    path /= fname;
    std::ifstream in(path);
    if (in.good())
    {
        json all;
        in >> all;
        for (auto v: all)
        {
            Volunteer vol;
            vol.from_json(all);
            volunteers.push_back(vol);
        }
    }
}

void Volunteers::save(
    std::filesystem::path path
)
{
    path /= fname;
    std::ofstream out(path, std::ios_base::trunc);
    json j;
    out << j << std::endl;

}

void Volunteers::add(
    Volunteer vol
)
{
    // TODO: Check for duplicates
    volunteers.push_back(vol);
}
