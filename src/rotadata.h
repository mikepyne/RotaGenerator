#ifndef ROTADATA_H
#define ROTADATA_H

#include <map>
#include <fstream>

#include <nlohmann/json.hpp>


template <class T>
class RotaData
{
public:
    /// \brief Load from file
    /// \param[in] in Stream to read volunteers from
    ///
    /// Read volunteers from a stream
    void load(
        std::iostream& in
    );

    /// \brief Save to file
    /// \param[in] out Stream to write volunteers to
    ///
    /// Write the volunteers to the stream
    void save(
        std::iostream& out
    );

    /// \brief Add a Volunteer to the collection
    /// \param[in] vol Volunteer to add
    /// \returns true if the Volunteer was added
    bool add(
        const T& item
    );

    /// \brief Count of volunteers
    int count() const {return data.size();};

    /// \brief Get a Volunteer
    /// \param id of the Volunteer to get
    /// \returns the requested Volunteer
    T& at(
        const std::string& id
    );

    /// \brief Erase a Volunteer
    /// \param id of the Volunteer to erase
    /// \returns the number of elements erased
    int erase(
        const std::string& id
    );

    /// \brief Update a Volunteer
    /// \param id of the Volunteer to update
    /// \param v the updated Volunteer
    void update(
        const std::string& id,
        const T& value
    );

private:
    std::map<std::string, T> data;
};

template <class T>
void RotaData<T>::load(
    std::iostream& in
)
{
    in.peek();
    if (in.good() && !in.eof())
    {
        nlohmann::json all;
        in >> all;
        for (auto& [key, value]: all.items())
        {
            T item(value);
            data.emplace(std::make_pair(key, item));
        }
    }
}

template <class T>
void RotaData<T>::save(
    std::iostream& out
)
{
    nlohmann::json j = data;
    out << j << std::endl;
    out.flush();
}

template <class T>
bool RotaData<T>::add(
    const T& item
)
{
    for (auto& [key, value]: data)
    {
        if (value == item)
        {
            return false;
        }
    }
    auto id = 1;
    std::string new_key {std::to_string(id)};
    if (data.size() > 0)
    {
        auto last_key = data.crbegin()->first;
        id = std::stoi(last_key) + 1;
        new_key = std::to_string(id);
    }
    if (data.count(new_key) == 0)
    {
        data.emplace(std::make_pair(new_key, item));
    }
    return true;
}

template <class T>
T& RotaData<T>::at(
    const std::string& id
)
{
    return data.at(id);
}

template <class T>
int RotaData<T>::erase(
    const std::string& id
)
{
    return data.erase(id);
}

template <class T>
void RotaData<T>::update(
    const std::string& id,
    const T& item
)
{
    data.at(id) = item;
}

#endif // ROTADATA_H
