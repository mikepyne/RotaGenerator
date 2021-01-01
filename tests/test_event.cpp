#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include "test_event.h"

TEST_CASE("Comparing Events", "[Event]")
{
    Event a {"label", "description", 2};
    Event b {"label", "description", 2};
    Event c {"lbl", "desc", 1};

    CHECK(a == b);
    CHECK_FALSE(a == c);
}

TEST_CASE("Event to Json", "[Event]")
{
    Event a {"label", "description", 2};

    nlohmann::json expected
    {
        {"label", "label"},
        {"description", "description"},
        {"volsNeeded", 2}
    };

    nlohmann::json j = a;

    REQUIRE(j == expected);
}

TEST_CASE("Event From Json", "[Event]")
{
    nlohmann::json from
    {
        {"label", "label"},
        {"description", "description"},
        {"volsNeeded", 2}
    };

    Event a;
    SECTION("Assign")
    {
        a = from;
    }

    SECTION("Construct")
    {
        a = Event(from);
    }

    CHECK(a.get_label() == "label");
    CHECK(a.get_description() == "description");
    CHECK(a.get_vols_needed() == 2);
}

TEST_CASE("Event with a Bad Key", "[Event]")
{
    nlohmann::json from
    {
        {"label", "label"},
        {"desc", "description"},
        {"volsNeeded", 2}
    };

    SECTION("Construct")
    {
        REQUIRE_THROWS_AS(Event(from), nlohmann::json::out_of_range);
    }

    SECTION("Assign")
    {
        Event e;
        REQUIRE_THROWS_AS(e = from, nlohmann::json::out_of_range);
    }
}

