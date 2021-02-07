#ifndef ROTADATA_H
#define ROTADATA_H

#include <map>
#include <fstream>
#include <type_traits>
#include <algorithm>

#include <nlohmann/json.hpp>

#include "rgexception.h"
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
    /// \returns true if the item is erased
    bool erase(
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
        return data[data_lbl].size();
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
    throw(RGException(RGException::errors::invalid, id));
}

template <class T>
bool RotaData<T>::erase(
    int id
)
{
    auto f = std::find_if(std::begin(data[data_lbl]), std::end(data[data_lbl]),
                          [&id](nlohmann::json& j){return j.at("id") == id;});

    if (f != std::end(data[data_lbl]))
    {
        data[data_lbl].erase(f);
        return true;
    }
    return false;
}

template <class T>
void RotaData<T>::update(
    int id,
    const T& item
)
{
    auto d = std::find_if(std::begin(data[data_lbl]), std::end(data[data_lbl]),
                          [&id, &item](nlohmann::json& j){return item == T(j);});

    auto f = std::find_if(std::begin(data[data_lbl]), std::end(data[data_lbl]),
                          [&id](nlohmann::json& j){return j.at("id") == id;});

    if (d != std::end(data[data_lbl]))
    {
        throw RGException(RGException::errors::duplicate, id, T(*d).get_id());
    }
    if (f == std::end(data[data_lbl]))
    {
        throw RGException(RGException::errors::invalid, id, -1);
    }
    *f = item;
}

#endif // ROTADATA_H
