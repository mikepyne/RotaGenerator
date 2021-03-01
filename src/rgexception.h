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
        duplicate,      ///< Duplicate item in list
        invalid,        ///< Invalid ID given
        missing_key     ///< Missing key
    };

    /// \brief Construct an exception
    /// \param[in] e The error being reported
    /// \param[in] i The ID of the item the error is for
    /// \param[in] o The other ID (if applicable)
    /// \param[in] k The key the error relates to
    ///
    /// The error being reported must be specified; the remaining parameters
    /// depend on what error is being reported.
    RGException(
        errors e,
        int i = -1,
        int o = -1,
        const std::string& k = ""
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
    std::string key {""};       ///< Key causing the error
    std::string w {""};         ///< The error message
};

#endif // RGEXCEPTION_H
