#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include "rgexception.h"
#include "test_event.h"

using Catch::Matchers::Message;
using nlohmann::json;
using namespace rg;

TEST_CASE("Comparing Events", "[Event]")
{
    Event a {1, "label", "description", 2, {1, 2}, 1};
    Event b {2, "label", "description", 2, {1, 2}, 1};
    Event c {3, "lbl", "desc", 1, {3, 4}, 2};

    CHECK(a == b);
    CHECK_FALSE(a == c);
    CHECK(a != c);
    CHECK_FALSE(a != b);
}

TEST_CASE("Event to Json", "[Event]")
{
    nlohmann::json expected;
    nlohmann::json j;
    SECTION("No day")
    {
        Event a {1, "label", "description", 2, {1, 2}};

        expected = {{"day", 8},
                    {"id", 1},
                    {"label", "label"},
                    {"description", "description"},
                    {"volsNeeded", 2},
                    {"volunteers", {1, 2}}};

        j = a;
        REQUIRE(j == expected);
    }

    SECTION("No volunteers")
    {
        Event a {1, "label", "description", 2, {}, 1};

        expected = {{"day", 1},
                    {"id", 1},
                    {"label", "label"},
                    {"description", "description"},
                    {"volsNeeded", 2},
                    {"volunteers", json::array()}};

        j = a;
        REQUIRE(j == expected);
    }
}

TEST_CASE("Event From Json", "[Event]")
{
    nlohmann::json from {{"day", 2},
                         {"id", 1},
                         {"label", "label"},
                         {"description", "description"},
                         {"volsNeeded", 2},
                         {"volunteers", {1, 2}}};

    Event a;
    Event b;
    SECTION("Assign")
    {
        a = from;
        b = a;
        CHECK(a.get_id() == 1);
        CHECK(a.get_label() == "label");
        CHECK(a.get_description() == "description");
        CHECK(a.get_vols_needed() == 2);
        CHECK(a.get_volunteers() == std::vector<int> {1, 2});
        CHECK(a.get_day() == 2);

        CHECK(a == b);
    }

    SECTION("Construct")
    {
        a = Event(from);
        CHECK(a.get_id() == 1);
        CHECK(a.get_label() == "label");
        CHECK(a.get_description() == "description");
        CHECK(a.get_vols_needed() == 2);
        CHECK(a.get_volunteers() == std::vector<int> {1, 2});
        CHECK(a.get_day() == 2);
    }

    SECTION("No volunteers")
    {
        from = {{"day", 2},
                {"id", 1},
                {"label", "label"},
                {"description", "description"},
                {"volsNeeded", 2},
                {"volunteers", json::array()}};
        a    = from;
        CHECK(a.get_id() == 1);
        CHECK(a.get_label() == "label");
        CHECK(a.get_description() == "description");
        CHECK(a.get_vols_needed() == 2);
        CHECK(a.get_volunteers() == std::vector<int> {});
        CHECK(a.get_day() == 2);
    }

    SECTION("No day")
    {
        from = {{"id", 1},
                {"label", "label"},
                {"description", "description"},
                {"volsNeeded", 2},
                {"volunteers", {1, 2}}};
        a    = from;
        CHECK(a.get_id() == 1);
        CHECK(a.get_label() == "label");
        CHECK(a.get_description() == "description");
        CHECK(a.get_vols_needed() == 2);
        CHECK(a.get_volunteers() == std::vector<int> {1, 2});
        CHECK(a.get_day() == 8);
    }
}

TEST_CASE("Event missing volunteers", "[Event]")
{
    nlohmann::json no_vs {{"id", 1},
                          {"label", "label"},
                          {"description", "description"},
                          {"volsNeeded", 2}};

    Event e;
    SECTION("Assign")
    {
        REQUIRE_THROWS_MATCHES(e = no_vs,
                               RGException,
                               Message("Key volunteers is missing from ID 1"));
    }

    SECTION("Construct")
    {
        REQUIRE_THROWS_MATCHES(e = Event(no_vs),
                               RGException,
                               Message("Key volunteers is missing from ID 1"));
    }
}

TEST_CASE("Event with a Bad Key", "[Event]")
{
    nlohmann::json from {{"label", "label"},
                         {"desc", "description"},
                         {"volsNeeded", 2}};

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

TEST_CASE("Adding volunteers to event", "[Event]")
{
    Event            e(1, "Label", "An event", 1, {1, 2});
    std::vector<int> to_add;

    SECTION("No duplicates")
    {
        to_add = {3, 4};

        REQUIRE_NOTHROW(e.add_volunteers(to_add));
        REQUIRE(e.get_volunteers() == std::vector<int> {1, 2, 3, 4});
    }

    SECTION("Duplicates")
    {
        to_add = {2, 3};
        REQUIRE_NOTHROW(e.add_volunteers(to_add));
        REQUIRE(e.get_volunteers() == std::vector<int> {1, 2, 3});
    }

    SECTION("High to low")
    {
        Event e2(1, "Label", "An event", 1, {9, 8});
        to_add = {7, 6};

        REQUIRE_NOTHROW(e2.add_volunteers(to_add));
        REQUIRE(e2.get_volunteers() == std::vector<int> {6, 7, 8, 9});
    }

    SECTION("Opposite order")
    {
        to_add = {2, 1};

        REQUIRE_NOTHROW(e.add_volunteers(to_add));
        REQUIRE(e.get_volunteers() == std::vector<int> {1, 2});
    }
}

TEST_CASE("Removing volunteers from event", "[Event]")
{
    Event            e(1, "Label", "An event", 2, {1, 2, 3});
    std::vector<int> to_remove;

    SECTION("Remove single volunteer")
    {
        to_remove = {1};
        REQUIRE_NOTHROW(e.remove_volunteers(to_remove));
        REQUIRE(e.get_volunteers() == std::vector<int> {2, 3});
    }

    SECTION("Remove multiple volunteers")
    {
        to_remove = {1, 3};
        REQUIRE_NOTHROW(e.remove_volunteers(to_remove));
        REQUIRE(e.get_volunteers() == std::vector<int> {2});
    }
}

TEST_CASE("Day to String")
{
    SECTION("Sunday")
    {
        REQUIRE(Event::day_to_string(0) == "Sunday");
        REQUIRE(Event::day_to_string(7) == "Sunday");
    }

    SECTION("Saturday") { REQUIRE(Event::day_to_string(6) == "Saturday"); }

    SECTION("No Day") { REQUIRE(Event::day_to_string(8) == ""); }
}
