#include <sstream>
#include <string_view>
#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include "mock_volunteer.h"
#include "test_volunteers.h"


TEST_CASE("Load from empty stream", "[Volunteers]")
{
    Volunteers vols;
    std::stringstream in;
    REQUIRE_NOTHROW(vols.load(in));
    CHECK(vols.count() == 0);
}

TEST_CASE("Load volunteers", "[Volunteers")
{
    Volunteers vols;
    std::stringstream in;

    in << R"({"1": {"email":"email","firstName":"First Name",)"
       << R"("phoneHome":"home","lastName":"Last name",)"
       << R"("phoneMobile":"mobile"},"2": {"email":"m@p","firstName":"Christian",)"
       << R"("phoneHome":"One","lastName":"Surname",)"
       << R"("phoneMobile":"Two"}})";

    REQUIRE_NOTHROW(vols.load(in));
    CHECK(vols.count() == 2);
}

TEST_CASE("Load volunteers with a bad key", "[Volunteers]")
{
    Volunteers vols;
    std::stringstream in;
    in << R"({"1": {"email":"email","firstName":"First Name",)"
       << R"("homePhone":"home","lastName":"Last name",)"
       << R"("phoneMobile":"mobile"}})";

    REQUIRE_THROWS_AS(vols.load(in), json::out_of_range);
    CHECK(vols.count() == 0);
}

TEST_CASE("No duplicate Volunteers", "[Volunteers]")
{
    Volunteers vols;
    MockVolunteer v1;
    MockVolunteer v2;

    REQUIRE(vols.add(v1));
    REQUIRE_FALSE(vols.add(v1));

    REQUIRE(vols.count() == 1);
}

TEST_CASE("Save Empty Volunteers", "[Volunteers]")
{
    std::stringstream expected;
    expected << "{}" << std::endl;
    std::stringstream out;
    Volunteers vols;
    vols.save(out);
     REQUIRE(out.str() == expected.str());
}

TEST_CASE("Save Volunteers", "[Volunteers]")
{
    std::stringstream expected;
    expected << R"({"1":{"email":"email","firstName":"First name",)"
             << R"("lastName":"Last name","phoneHome":"home",)"
             << R"("phoneMobile":"mobile"},"2":{"email":"m@p",)"
             << R"("firstName":"Christian","lastName":"Surname",)"
             << R"("phoneHome":"One","phoneMobile":"Two"}})"
             << std::endl;

    Volunteer v1("First name", "Last name", "home", "mobile", "email");
    Volunteer v2("Christian", "Surname", "One", "Two", "m@p");;
    std::stringstream out;
    Volunteers vols;
    vols.add(v1);
    vols.add(v2);
    vols.save(out);

    REQUIRE(out.str() == expected.str());
}


TEST_CASE("Getting a Volunteer", "[Volunteers]")
{
    Volunteers vols;
    Volunteer v1("First name", "Last name", "home", "mobile", "email");
    Volunteer v2("Christian", "Surname", "One", "Two", "m@p");

    vols.add(v1);
    vols.add(v2);

    REQUIRE(vols.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(vols.at("1") == v1);
        REQUIRE(vols.at("2") == v2);
    }

    SECTION("Bad ID")
    {
        REQUIRE_THROWS_AS(vols.at("3"), std::out_of_range);
    }
}

TEST_CASE("Deleting a volunteer", "[Volunteers]")
{
    Volunteers vols;
    Volunteer v1("First name", "Last name", "home", "mobile", "email");
    Volunteer v2("Christian", "Surname", "One", "Two", "m@p");

    vols.add(v1);
    vols.add(v2);

    REQUIRE(vols.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(vols.erase("1") == 1);
        REQUIRE(vols.count() == 1);
        REQUIRE_THROWS_AS(vols.at("1"), std::out_of_range);
    }

    SECTION("Bad ID")
    {
        REQUIRE(vols.erase("3") == 0);
        REQUIRE(vols.count() == 2);
    }
}

TEST_CASE("Edit a volunteer", "[Volunteers]")
{
    Volunteers vols;
    Volunteer v1("First name", "Last name", "home", "mobile", "email");
    Volunteer v2("Christian", "Surname", "One", "Two", "m@p");

    vols.add(v1);
    vols.add(v2);

    REQUIRE(vols.count() == 2);

    SECTION("Edit Good ID")
    {
        Volunteer v = vols.at("1");

        v.set_first_name("New first name");
        vols.update("1", v);

        Volunteer w = vols.at("1");
        REQUIRE(w.get_first_name() == "New first name");
    }

    SECTION("Edit Bad ID")
    {
        REQUIRE_THROWS_AS(vols.update("3", v1), std::out_of_range);
        REQUIRE(vols.count() == 2);
    }
}
