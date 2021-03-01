#include <fmt/core.h>

#include "rgexception.h"

RGException::RGException(
    errors e,
    int i,
    int o,
    const std::string& k
) : error(e),
    id(i),
    other_id(o),
    key(k)
{
    switch (error)
    {
        case errors::duplicate:
            w = fmt::format("Unable to update item {}; duplicate at {}.",
                            id, other_id);

            break;
        case errors::invalid:
            w = fmt::format("Invalid ID ({})", id);
            break;
        case errors::missing_key:
            w = fmt::format("Missing key ({}) in JSON", key);
    };
}
