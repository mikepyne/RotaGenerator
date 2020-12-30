#ifndef VOLUNTEERS_H
#define VOLUNTEERS_H

#include <string>
#include <iostream>
#include <map>

#include "volunteer.h"


static std::string_view volunteers_fname{"volunteers.txt"};

/// \class Volunteers
/// \brief Collection of Volunteer objects
class Volunteers
{
public:
    Volunteers() = default;

    /// \brief Load from file
    /// \param[in] in Stream to read volunteers from
    ///
    /// Read volunteers from a stream
    void load(
        std::istream& in
    );

    /// \brief Save to file
    /// \param[in] out Stream to write volunteers to
    ///
    /// Write the volunteers to the stream
    void save(
        std::ostream& out
    );

    /// \brief Add a volunteer to the collection
    /// \param[in] vol Volunteer to add
    /// \returns true if the volunteer was added
    bool add(
        Volunteer vol
    );

    /// \brief Count of volunteers
    int count() {return volunteers.size();}

    /// \brief Get a volunteer
    /// \param id of the volunteer to get
    Volunteer& at(
        const std::string& id
    );

    /// \brief Erase a volunteer
    /// \param id of the volunteer to erase
    /// \returns the number of elements erased
    int erase(
        const std::string& id
    );

    /// \brief Update a volunteer
    /// \param id of the volunteer to update
    /// \param v the updated volunteer
    void update(
        const std::string& id,
        const Volunteer& v
    );

private:
    std::map<std::string, Volunteer> volunteers;  ///< The volunteers
};

#endif // VOLUNTEERS_H
