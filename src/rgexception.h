#ifndef RGEXCEPTION_H
#define RGEXCEPTION_H

#include <exception>
#include <string>

#include <fmt/core.h>


/// \class RGException
/// \brief Report an error with an item
class RGException : public std::exception
{
public:
    /// \brief Errors when updating an item
    enum class errors
    {
        duplicate,  ///< Duplicate item in list
        invalid     ///< Invalid ID given
    };

    /// \brief Construct an exception
    /// \param e The error being reported
    /// \param i the ID of the item the error is for
    /// \param o The other ID (if applicable)
    RGException(
        errors e,
        int i,
        int o = -1
    );

    /// \brief Returns the explanatory string
    const char* what() const noexcept override
    {
        return w.c_str();
    };

protected:
    errors      error;          ///< Which error
    int         id {0};         ///< ID of item with error
    int         other_id {0};   ///< ID of other item
    std::string w {""};         ///< The error message
};

#endif // RGEXCEPTION_H
