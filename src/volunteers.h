#ifndef VOLUNTEERS_H
#define VOLUNTEERS_H

#include <string>
#include <iostream>
#include <vector>

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
    void add(
        Volunteer vol
    );

    /// \brief Count of volunteers
    int count() {return volunteers.size();}

private:
    std::vector<Volunteer> volunteers;  ///< The volunteers
};

#endif // VOLUNTEERS_H
