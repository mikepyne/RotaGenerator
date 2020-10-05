#include <catch2/catch.hpp>

#include "volunteer.h"
#include "volunteers.h"

TEST_CASE("Don't add duplicates", "[volunteers]")
{
    Volunteer v(1, "First name", "Last name", "home", "mobile", "email");

    Volunteers vol;

    vol.add(v);
    vol.add(v);

    REQUIRE(vol.count() == 1);
}
