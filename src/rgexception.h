#ifndef RGEXCEPTION_H
#define RGEXCEPTION_H

#include <exception>
#include <string>

#include <fmt/core.h>

namespace rg
{
/// \class RGException
/// \brief Base class for exceptions in the RotaGenerator
///
/// Specific exceptions are defined as derived classes, so specifc elements
/// for the description can be supplied.
class RGException : public std::exception
{
public:
    /// \brief Get the description of the exception
    /// \returns The description
    const char* what() const noexcept override { return w.c_str(); };

protected:
    std::string w {""};    ///< The error message
};

/// \class Duplicate
/// \brief Duplicate item exists in the data
class Duplicate : public RGException
{
public:
    /// \brief Create a Duplicate exception
    /// \param[in] id The id supplied
    /// \param[in] other_id The of the item that matched
    Duplicate(int id, int other_id)
    {
        w = fmt::format("A duplicate item to {} was found at {}", id, other_id);
    };
};

/// \class Invalid
/// \brief An invalid ID has been supplied
class Invalid : public RGException
{
public:
    /// \brief Construct the Invalid exception
    /// \param[in] id The ID supplied (i.e. the invalid ID)
    Invalid(int id) { w = fmt::format("Invalid ID ({})", id); }
};

/// \class MissingKey
/// \brief A key is missing from a JSON item
class MissingKey : public RGException
{
public:
    /// \brief Construct the MissingKey exception
    /// \param[in] id The ID with the missing key
    /// \param[in] key The key that is missing
    MissingKey(int id, std::string key)
    {
        w = fmt::format("Key {} is missing from ID {}", key, id);
    }
};

/// \class LoadError
/// \brief Unable to load a data file
class LoadError : public RGException
{
public:
    /// \brief Consturct the exception
    LoadError(std::string details)
    {
        w = fmt::format("Error loading data: {}", details);
    }
};

}    // namespace rg

#endif    // RGEXCEPTION_H
