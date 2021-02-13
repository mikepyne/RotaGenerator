#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include "test_volunteer.h"


TEST_CASE("Compare Volunteer", "[Volunteer]")
{
    Volunteer a {1, "First", "Last", "Home", "Mobile", "Email"};
    Volunteer b {2, "First", "Last", "Home", "Mobile", "Email"};
    Volunteer c {3, "Forename", "Surname", "Home", "Mobile", "Email"};

    CHECK(a == b);
    CHECK(a != c);
    CHECK_FALSE(a == c);
    CHECK_FALSE(a != b);
}

TEST_CASE("Volunteer To Json", "[Volunteer]")
{
    Volunteer a {1, "First", "Last", "Home", "Mobile", "Email"};
    nlohmann::json expected {
        {"id", 1},
        {"email", "Email"},
        {"firstName", "First"},
        {"lastName", "Last"},
        {"phoneHome", "Home"},
        {"phoneMobile", "Mobile"},
    };

    nlohmann::json j = a;
    REQUIRE(j == expected);
}

TEST_CASE("Volunteer From Json", "[Volunteer]")
{
    nlohmann::json from {
        {"id", 1},
        {"firstName", "First"},
        {"lastName", "Last"},
        {"phoneHome", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"}
    };

    Volunteer v;

    SECTION("Assign")
    {
        v = from;
    }

    SECTION("Construct")
    {
        v = Volunteer(from);
    }

    REQUIRE(v.get_id() == 1);
    REQUIRE(v.get_first_name() == "First");
    REQUIRE(v.get_last_name() == "Last");
    REQUIRE(v.get_phone_home() == "Home");
    REQUIRE(v.get_phone_mobile() == "Mobile");
    REQUIRE(v.get_email() == "Email");
}

TEST_CASE("Volunteer with a Bad Key", "[Volunteer]")
{
    // With homePhone as a deliberately bad key
    nlohmann::json from {
        {"id", 1},
        {"firstName", "First"},
        {"lastName", "Last"},
        {"homePhone", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"},
    };

    SECTION("Construct")
    {
        REQUIRE_THROWS_AS(Volunteer(from), nlohmann::json::out_of_range);
    }

    SECTION("Assign")
    {
        Volunteer v;
        REQUIRE_THROWS_AS(v = from, nlohmann::json::out_of_range);
    }
}

TEST_CASE("Volunteer's Name", "[Volunteer]")
{
    auto v = Volunteer();
    v.set_first_name("John");
    v.set_last_name("Smith");

    REQUIRE(v.get_name() == "John Smith");
}
