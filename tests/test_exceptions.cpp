#include <catch2/catch.hpp>

#include "rgexception.h"

using Catch::Matchers::Equals;
using namespace rg;

TEST_CASE("Update item exceptions", "[Exceptions]")
{
    SECTION("Duplicate")
    {
        auto e = rg::Duplicate(1, 2);
        REQUIRE_THAT(e.what(), Equals("A duplicate item to 1 was found at 2"));
    }

    SECTION("Invalid")
    {
        auto e = rg::Invalid(1);
        REQUIRE_THAT(e.what(), Equals("Invalid ID (1)"));
    }
}
