#include <catch2/catch.hpp>

#include "volunteer.h"

TEST_CASE("Test comparison", "[volunteer]")
{
    Volunteer a(1, "First", "Last", "Home", "Mobile", "Email");
    Volunteer b(2, "First", "Last", "Home", "Mobile", "Email");

    Volunteer c(3, "Forename", "Surname", "Home", "Mobile", "Email");

    REQUIRE(a == b);
    REQUIRE_FALSE(a == c);
    REQUIRE(a != c);
}
