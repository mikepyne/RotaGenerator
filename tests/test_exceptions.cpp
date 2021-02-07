#include <catch2/catch.hpp>

#include "rgexception.h"

using Catch::Matchers::Equals;

TEST_CASE("Update item exceptions", "[Exceptions]")
{
    SECTION("Duplicate")
    {
        auto e = RGException(RGException::errors::duplicate, 1, 2);
        REQUIRE_THAT(e.what(), Equals("Unable to update item 1; duplicate at 2."));
    }

    SECTION("Invalid")
    {
        auto e = RGException(RGException::errors::invalid, 1);
        REQUIRE_THAT(e.what(), Equals("Invalid ID (1)"));
    }
}
