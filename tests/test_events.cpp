#include <sstream>
#include <string_view>
#include <catch2/catch.hpp>

#include "event.h"
#include "test_events.h"

#include "rotadata.h"


TEST_CASE("Load empty events", "[Events]")
{
    RotaData<Event> events;
    std::stringstream in;
    REQUIRE_NOTHROW(events.load(in));
    CHECK(events.count() == 0);
}

TEST_CASE("Load events", "[Events]")
{
    RotaData<Event> events;
    std::stringstream in;

    in << R"({"1":{"label":"label","description":"Description",)"
       << R"("volsNeeded":1},"2":{"label":"lbl","description":"desc",)"
       << R"("volsNeeded":3}})";

    REQUIRE_NOTHROW(events.load(in));
    CHECK(events.count() == 2);
}

TEST_CASE("Load Events with a bad key", "[Events]")
{
    RotaData<Event> events;
    std::stringstream in;
    in << R"({"1":{"notlabel":"label","description":"Description",)"
       << R"("volsNeeded":1}})";

    REQUIRE_THROWS_AS(events.load(in), json::out_of_range);
    CHECK(events.count() == 0);
}

TEST_CASE("No duplicate Events", "[Events]")
{
    RotaData<Event> events;
    Event e1;
    Event e2;

    REQUIRE(events.add(e1));
    REQUIRE_FALSE(events.add(e1));

    REQUIRE(events.count() == 1);
}

TEST_CASE("Save Empty Events", "[Events]")
{
    std::stringstream expected;
    expected << "{}" << std::endl;
    std::stringstream out;
    RotaData<Event> events;
    events.save(out);
    REQUIRE(out.str() == expected.str());
}

TEST_CASE("Save Events", "[Events]")
{
    std::stringstream expected;
    expected << R"({"1":{"description":"Description","label":"label",)"
             << R"("volsNeeded":1},"2":{"description":"desc","label":"lbl",)"
             << R"("volsNeeded":3}})"
             << std::endl;

    Event e1("label", "Description", 1);;
    Event e2("lbl", "desc", 3);
    std::stringstream out;
    RotaData<Event> events;
    events.add(e1);
    events.add(e2);
    events.save(out);

    REQUIRE(out.str() == expected.str());
}


TEST_CASE("Getting an Event", "[Events]")
{
    RotaData<Event> events;
    Event e1("label", "description", 1);
    Event e2("lbl", "desc", 3);

    events.add(e1);
    events.add(e2);

    REQUIRE(events.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(events.at("1") == e1);
        REQUIRE(events.at("2") == e2);
    }

    SECTION("Bad ID")
    {
        REQUIRE_THROWS_AS(events.at("3"), std::out_of_range);
    }
}

TEST_CASE("Deleting an Event", "[Events]")
{
    RotaData<Event> events;
    Event e1("label", "description", 1);
    Event e2("lbl", "desc", 3);

    events.add(e1);
    events.add(e2);

    REQUIRE(events.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(events.erase("1") == 1);
        REQUIRE(events.count() == 1);
        REQUIRE_THROWS_AS(events.at("1"), std::out_of_range);
    }

    SECTION("Bad ID")
    {
        REQUIRE(events.erase("3") == 0);
        REQUIRE(events.count() == 2);
    }
}

TEST_CASE("Edit an Event", "[Events]")
{
    RotaData<Event> events;
    Event e1("label", "description", 1);
    Event e2("lbl", "desc", 3);

    events.add(e1);
    events.add(e2);

    REQUIRE(events.count() == 2);

    SECTION("Edit Good ID")
    {
        Event e = events.at("1");
        e.set_label("New Label");
        events.update("1", e);

        Event w = events.at("1");
        REQUIRE(w.get_label() == "New Label");
    }

    SECTION("Edit Bad ID")
    {
        REQUIRE_THROWS_AS(events.update("3", e1), std::out_of_range);
        REQUIRE(events.count() == 2);
    }
}
