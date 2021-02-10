#include <iostream>
#include <sstream>
#include <string_view>
#include <catch2/catch.hpp>
#include <trompeloeil.hpp>

#include "mock_volunteer.h"
#include "test_volunteers.h"

#include "rotadata.h"

using Catch::Matchers::Message;

TEST_CASE("Loading volunteers", "[Volunteers]")
{
    RotaData<MockVolunteer> vols;
    std::stringstream in;

    SECTION("Empty")
    {
        REQUIRE_NOTHROW(vols.load(in));
        REQUIRE(vols.count() == 0);
    }

    SECTION("Good load")
    {
        in << R"({"data":[{"email":"email","firstName":"First Name","id":1,)"
           << R"("phoneHome":"home","lastName":"Last name",)"
           << R"("phoneMobile":"mobile"},{"email":"m@p","firstName":"Christian",)"
           << R"("id":2,"phoneHome":"One","lastName":"Surname",)"
           << R"("phoneMobile":"Two"}]})";

        REQUIRE_NOTHROW(vols.load(in));
        REQUIRE(vols.count() == 2);
    }

    SECTION("Bad key")
    {
        in << R"({"data": [{"email":"email","firstName":"First Name","id":1,)"
           << R"("homePhone":"home","lastName":"Last name",)"
           << R"("phoneMobile":"mobile"}]})";

        // Array contents aren't validated when loaded now, so loading with a bad key
        // won't throw an error.
        REQUIRE_NOTHROW(vols.load(in));
        REQUIRE(vols.count() == 1);

        REQUIRE_THROWS_AS(vols.at(1), nlohmann::json::out_of_range);
    }

    SECTION("No duplicates")
    {
        MockVolunteer v1;
        MockVolunteer v2;

        REQUIRE_CALL(v1, get_id())
            .TIMES(AT_LEAST(1))
            .RETURN(1);

        REQUIRE_CALL(v2, eq(ANY(MockVolunteer)))
            .RETURN(true);

        REQUIRE(vols.add(v1) == 1);
        REQUIRE(vols.add(v2) == -1);

        REQUIRE(vols.count() == 1);
    }

    SECTION("Bad JSON")
    {
        in << R"({"data": [{"email":"email""firstName":"First Name", "id":1,)"
           << R"("homePhone":"123","lastName":"Last name","phoneMobile":"456"}]})";

        REQUIRE_THROWS_AS(vols.load(in), nlohmann::json::parse_error);
    }
}

TEST_CASE("Save Volunteers", "[Volunteers]")
{
    std::stringstream expected;
    std::stringstream out;
    RotaData<MockVolunteer> vols;

    SECTION("Empty Save")
    {
        expected << "{}" << std::endl;

        vols.save(out);
        REQUIRE(out.str() == "null");
    }

    SECTION("Good save")
    {
        std::stringstream expected;
        expected << R"({"data":[{"email":"email","firstName":"First name","id":1,)"
                 << R"("lastName":"Last name","phoneHome":"home",)"
                 << R"("phoneMobile":"mobile"},{"email":"m@p",)"
                 << R"("firstName":"Christian","id":2,"lastName":"Surname",)"
                 << R"("phoneHome":"One","phoneMobile":"Two"}]})"
                 << std::endl;

        MockVolunteer v1(1, "First name", "Last name", "home", "mobile", "email");
        MockVolunteer v2(2, "Christian", "Surname", "One", "Two", "m@p");;

        ALLOW_CALL(v1, get_id())
            .RETURN(1);

        ALLOW_CALL(v2, get_id())
            .RETURN(2);

        ALLOW_CALL(v2, eq(ANY(MockVolunteer)))
            .RETURN(false);

        vols.add(v1);
        vols.add(v2);
        vols.save(out);

        REQUIRE(out.str() != expected.str());
    }
}

TEST_CASE("Getting a Volunteer", "[Volunteers]")
{
    RotaData<Volunteer> vols;
    Volunteer v1(1, "First name", "Last name", "home", "mobile", "email");
    Volunteer v2(2, "Christian", "Surname", "One", "Two", "m@p");

    vols.add(v1);
    vols.add(v2);

    REQUIRE(vols.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(vols.at(1) == v1);
        REQUIRE(vols.at(2) == v2);
    }

    SECTION("Bad ID")
    {
        REQUIRE_THROWS_MATCHES(vols.at(3), RGException,
                               Message("Invalid ID (3)"));
    }
}

TEST_CASE("Deleting a volunteer", "[Volunteers]")
{
    RotaData<Volunteer> vols;
    Volunteer v1(1, "First name", "Last name", "home", "mobile", "email");
    Volunteer v2(2, "Christian", "Surname", "One", "Two", "m@p");

    vols.add(v1);
    vols.add(v2);

    REQUIRE(vols.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(vols.erase(1));
        REQUIRE(vols.count() == 1);
        REQUIRE_THROWS_MATCHES(vols.at(1), RGException,
                               Message("Invalid ID (1)"));
    }

    SECTION("Bad ID")
    {
        REQUIRE_FALSE(vols.erase(3));
        REQUIRE(vols.count() == 2);
    }
}

TEST_CASE("Edit a volunteer", "[Volunteers]")
{
    RotaData<Volunteer> vols;
    Volunteer v1(1, "First name", "Last name", "home", "mobile", "email");
    Volunteer v2(2, "Christian", "Surname", "One", "Two", "m@p");

    vols.add(v1);
    vols.add(v2);

    REQUIRE(vols.count() == 2);

    SECTION("Edit Good ID")
    {
        Volunteer v = vols.at(1);

        v.set_first_name("New first name");
        vols.update(1, v);

        Volunteer w = vols.at(1);
        REQUIRE(w.get_first_name() == "New first name");
    }

    SECTION("Edit Bad ID")
    {
        Volunteer v3(3, "Jelly", "Crainer", "01234 567890", "07912 345678",
                     "jelly@crainer.com");

        REQUIRE_THROWS_MATCHES(vols.update(3, v3), RGException,
                               Message("Invalid ID (3)"));

        REQUIRE(vols.count() == 2);
    }

    SECTION("Duplicate an existing item")
    {
        REQUIRE_THROWS_MATCHES(
            vols.update(2, v1),
            RGException,
            Message("Unable to update item 2; duplicate at 1."));

        REQUIRE(vols.count() == 2);
    }
}
