#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include "test_volunteer.h"


TEST_CASE("Compare Volunteer", "[Volunteer]")
{
    Volunteer a {"First", "Last", "Home", "Mobile", "Email"};
    Volunteer b {"First", "Last", "Home", "Mobile", "Email"};

    Volunteer c {"Forename", "Surname", "Home", "Mobile", "Email"};

    CHECK(a == b);
    CHECK_FALSE(a == c);
}

TEST_CASE("Volunteer To Json", "[Volunteer]")
{
    Volunteer a {"First", "Last", "Home", "Mobile", "Email"};
    nlohmann::json expected {
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
    std::string expected_id {"1"};
    nlohmann::json from {
        {"firstName", "First"},
        {"lastName", "Last"},
        {"phoneHome", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"}
    };

    Volunteer v = from;

    REQUIRE(v.get_first_name() == "First");
    REQUIRE(v.get_last_name() == "Last");
    REQUIRE(v.get_phone_home() == "Home");
    REQUIRE(v.get_phone_mobile() == "Mobile");
    REQUIRE(v.get_email() == "Email");
}

TEST_CASE("Construct from Json", "[Volunteer]")
{
    nlohmann::json from {
        {"firstName", "First"},
        {"lastName", "Last"},
        {"phoneHome", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"},
    };

    Volunteer v = Volunteer(from);

    REQUIRE(v.get_first_name() == "First");
    REQUIRE(v.get_last_name() == "Last");
    REQUIRE(v.get_phone_home() == "Home");
    REQUIRE(v.get_phone_mobile() == "Mobile");
    REQUIRE(v.get_email() == "Email");
}

TEST_CASE("Construct with bad key", "[Volunteer]")
{
    nlohmann::json from {
        {"firstName", "First"},
        {"lastName", "Last"},
        {"homePhone", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"},
    };

    REQUIRE_THROWS_AS(Volunteer(from), nlohmann::json::out_of_range);
}

TEST_CASE("Assign with bad key", "[Volunteer]")
{
    nlohmann::json from {
        {"firstName", "First"},
        {"lastName", "Last"},
        {"homePhone", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"},
    };
    Volunteer v;
    REQUIRE_THROWS_AS(v = from, nlohmann::json::out_of_range);
}
