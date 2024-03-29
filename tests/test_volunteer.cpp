#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include "test_volunteer.h"

using namespace rg;

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

TEST_CASE("Getters and Setters")
{
    Volunteer v;

    SECTION("ID")
    {
        v.set_id(1);
        REQUIRE(v.get_id() == 1);
    }

    SECTION("First Name")
    {
        v.set_first_name("Name");
        REQUIRE(v.get_first_name() == "Name");
    }

    SECTION("Last Name")
    {
        v.set_last_name("Last");
        REQUIRE(v.get_last_name() == "Last");
    }

    SECTION("Phone Home")
    {
        v.set_phone_home("Home");
        REQUIRE(v.get_phone_home() == "Home");
    }

    SECTION("Phone Mobile")
    {
        v.set_phone_mobile("Mobile");
        REQUIRE(v.get_phone_mobile() == "Mobile");
    }
}

TEST_CASE("Volunteer To Json", "[Volunteer]")
{
    Volunteer      a {1, "First", "Last", "Home", "Mobile", "Email"};
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
    nlohmann::json from {{"id", 1},
                         {"firstName", "First"},
                         {"lastName", "Last"},
                         {"phoneHome", "Home"},
                         {"phoneMobile", "Mobile"},
                         {"email", "Email"}};

    Volunteer v;

    SECTION("Assign") { v = from; }

    SECTION("Construct") { v = Volunteer(from); }

    Volunteer vb;
    vb = v;
    REQUIRE(v.get_id() == 1);
    REQUIRE(v.get_first_name() == "First");
    REQUIRE(v.get_last_name() == "Last");
    REQUIRE(v.get_phone_home() == "Home");
    REQUIRE(v.get_phone_mobile() == "Mobile");
    REQUIRE(v.get_email() == "Email");
    REQUIRE(v == vb);
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
    auto        v = Volunteer();
    std::string to_split("John Smith");
    std::string expected(to_split);
    std::string expFirst("John");
    std::string expLast("Smith");

    SECTION("Without splitting")
    {
        v.set_first_name("John");
        v.set_last_name("Smith");

        REQUIRE(v.get_name() == expected);
    }

    SECTION("Split, with no spaces")
    {
        to_split = "NoSpacesInMyName";
        expected = to_split;
        expFirst = "";

        v.set_name(to_split);
        REQUIRE(v.get_first_name() == expFirst);
        REQUIRE(v.get_last_name() == expected);
    }

    SECTION("Simple split")
    {
        to_split = "John Smith";

        v.set_name(to_split);
        REQUIRE(v.get_first_name() == expFirst);
        REQUIRE(v.get_last_name() == expLast);
    }

    SECTION("Double barrelled")
    {
        to_split = "John Smith Jones";
        expLast  = "Smith Jones";

        v.set_name(to_split);
        REQUIRE(v.get_first_name() == expFirst);
        REQUIRE(v.get_last_name() == expLast);
    }

    SECTION("Hyphenated first name")
    {
        to_split = "John-Paul Smith";
        expFirst = "John-Paul";

        v.set_name(to_split);
        REQUIRE(v.get_first_name() == expFirst);
        REQUIRE(v.get_last_name() == expLast);
    }

    SECTION("Hyphenated last name")
    {
        to_split = "John Paul-Smith";
        expLast  = "Paul-Smith";

        v.set_name(to_split);
        REQUIRE(v.get_first_name() == expFirst);
        REQUIRE(v.get_last_name() == expLast);
    }
}
