#ifndef ROTADATA_H
#define ROTADATA_H

#include <map>
#include <fstream>
#include <type_traits>
#include <algorithm>

#include <nlohmann/json.hpp>

#include "event.h"
#include "volunteer.h"

constexpr auto data_lbl = "data";

/// \brief Collection of data items
/// \tparam T an individual data item
///
/// A data item is a Volunteer or an Event. This template is a collection of
/// data items.
template <class T>
class RotaData
{
public:
    /// \brief Load from file
    /// \param[in] in Stream to read items from
    ///
    /// Read items from a stream containing JSON.
    /// The JSON will contain an array named either "Volunteers" or "Events".
    void load(
        std::iostream& in
    );

    /// \brief Save to file
    /// \param[in] out Stream to write volunteers to
    ///
    /// Write the items to the stream
    void save(
        std::iostream& out
    );

    /// \brief Add an item to the collection
    /// \param[in] item to add
    /// \returns the id of the new item
    ///
    /// TODO: How to handle the new id?
    /// Get next ID method?
    /// item is not const, because the ID will be set before adding it to the
    /// list.
    int add(
        T& item
    );

    /// \brief Count of items
    int count() const;

    /// \brief Get an item
    /// \param id of the item to get
    /// \returns the requested item
    T at(
        int id
    );

    /// \brief Erase an item
    /// \param id of the item to erase
    /// \returns the number of elements erased
    int erase(
        int id
    );

    /// \brief Update an item
    /// \param id of the item to update
    /// \param value the updated item
    void update(
        int id,
        const T& value
    );

protected:
    nlohmann::json  data;           ///< The data
    int             next_id {1};    ///< Next ID to use
};

template <class T>
void RotaData<T>::load(
    std::iostream& in
)
{
    in.peek();
    if (in.good() && !in.eof())
    {
        in >> data;
    }
    auto id = [&next_id = next_id](nlohmann::json j)
    {
        int current = j.at("id");
        if (current > next_id)
        {
            next_id = current + 1;
        }
    };
    std::for_each(std::begin(data[data_lbl]), std::end(data[data_lbl]), id);
}

template <class T>
void RotaData<T>::save(
    std::iostream& out
)
{
    out << data;
    out.flush();
}

template <class T>
int RotaData<T>::add(
    T& item
)
{
    // Check for duplicate
    auto f = std::find_if(std::begin(data[data_lbl]), std::end(data[data_lbl]),
                          [&item](nlohmann::json j){return item == T(j);});

    if (f == std::end(data[data_lbl]))
    {
        item.set_id(next_id);
        next_id++;
        data["data"].push_back(item);
        return item.get_id();
    }
    return -1;
}

template <class T>
int RotaData<T>::count() const
{
    try
    {
        return data["data"].size();
    }
    catch (nlohmann::json::type_error& e)
    {
        return 0;
    }
}

template <class T>
T RotaData<T>::at(
    int id
)
{
    auto f = std::find_if(std::begin(data[data_lbl]), std::end(data[data_lbl]),
                          [&id](nlohmann::json& j){return j.at("id") == id;});

    if (f != std::end(data[data_lbl]))
    {
        T item {*f};
        return item;
    }
    throw(std::runtime_error("Failed to find"));
}

template <class T>
int RotaData<T>::erase(
    int id
)
{
    return -1;
}

template <class T>
void RotaData<T>::update(
    int id,
    const T& item
)
{
    data.at(id) = item;
}

#endif // ROTADATA_H
