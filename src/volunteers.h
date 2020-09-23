#ifndef VOLUNTEERS_H
#define VOLUNTEERS_H

#include <string>
#include <filesystem>

#include <vector>

#include "volunteer.h"

/// \class Volunteers
/// \brief Collection of Volunteer objects
class Volunteers
{
public:
    Volunteers() = default;

    /// \brief Load from file
    /// \param[in] path Path to the volunteers file
    ///
    /// Load volunteers from a text file (volunteers.txt) containing a list of
    /// volunteers. The path contains the location of the file.
    void load(
        std::filesystem::path path
    );

    /// \brief Save to file
    /// \param[in] path Save volunteers to file
    ///
    /// Save the list of volunteers to the volunteers.txt file. The path
    /// contains the location of the file.
    void save(
        std::filesystem::path path
    );

    /// \brief Add a volunteer to the collection
    /// \param[in] vol Volunteer to add
    void add(
        Volunteer vol
    );

private:
    static constexpr auto fname{"volunteers.txt"};  ///< Name of the volunteers file

    std::vector<Volunteer> volunteers;  ///< The volunteers
};

#endif // VOLUNTEERS_H
