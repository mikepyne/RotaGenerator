#include <sstream>
#include <string_view>
#include <catch2/catch.hpp>

#include "mock_event.h"
#include "test_events.h"

#include "rotadata.h"

using Catch::Matchers::Message;

TEST_CASE("Loading events", "[Events]")
{
    RotaData<MockEvent> events;
    std::stringstream in;

    SECTION("Empty events")
    {
        REQUIRE_NOTHROW(events.load(in));
        CHECK(events.count() == 0);
    }

    SECTION("Load events")
    {
        in << R"({"data":[{"id":1,"label":"label","description":"Description",)"
           << R"("volsNeeded":1},{"id":2,"label":"lbl","description":"desc",)"
           << R"("volsNeeded":3}]})";

        REQUIRE_NOTHROW(events.load(in));
        CHECK(events.count() == 2);
    }

    SECTION("Bad key")
    {
        in << R"({"data":[{"id":1,"notlabel":"label","description":"Description",)"
           << R"("volsNeeded":1}]})";

        REQUIRE_NOTHROW(events.load(in));
        CHECK(events.count() == 1);

        REQUIRE_THROWS_AS(events.at(1), nlohmann::json::out_of_range);
    }

    SECTION("No duplicates")
    {
        MockEvent e1;
        MockEvent e2;

        REQUIRE_CALL(e1, get_id())
            .TIMES(AT_LEAST(1))
            .RETURN(1);

        REQUIRE_CALL(e2, eq(ANY(MockEvent)))
            .RETURN(true);

        REQUIRE(events.add(e1) == 1);
        REQUIRE(events.add(e2) == -1);

        REQUIRE(events.count() == 1);
    }

    SECTION("Bad JSON")
    {
        in << R"({"data": [{"id":1"label":"label","description":"Description",)"
           << R"("volsNeeded":1)}]})";

        REQUIRE_THROWS_AS(events.load(in), nlohmann::json::parse_error);
    }

}

TEST_CASE("Save Events", "[Events]")
{
    RotaData<MockEvent> events;
    std::stringstream expected;
    std::stringstream out;

    SECTION("Save empty events")
    {
        expected << "{}" << std::endl;

        events.save(out);
        REQUIRE(out.str() == "null");
    }

    SECTION("Good save")
    {
        expected << R"({"data":[{"description":"Description","id":1,"label":"label",)"
                 << R"("volsNeeded":1},{"description":"desc","id":2,)"
                 << R"("label":"lbl","volsNeeded":3}]})"
                 << std::endl;

        MockEvent e1(1, "label", "Description", 1);
        MockEvent e2(2, "lbl", "desc", 3);

        ALLOW_CALL(e1, get_id())
            .RETURN(1);

        ALLOW_CALL(e2, get_id())
            .RETURN(2);

        ALLOW_CALL(e2, eq(ANY(MockEvent)))
            .RETURN(false);

        events.add(e1);
        events.add(e2);
        events.save(out);

        REQUIRE(out.str() != expected.str());
    }
}


TEST_CASE("Getting an Event", "[Events]")
{
    RotaData<Event> events;
    Event e1(1, "label", "description", 1);
    Event e2(2, "lbl", "desc", 3);

    events.add(e1);
    events.add(e2);

    REQUIRE(events.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(events.at(1) == e1);
        REQUIRE(events.at(2) == e2);
    }

    SECTION("Bad ID")
    {
        REQUIRE_THROWS_MATCHES(events.at(3), RGException,
                               Message("Invalid ID (3)"));
    }
}

TEST_CASE("Deleting an Event", "[Events]")
{
    RotaData<Event> events;
    Event e1(1, "label", "description", 1);
    Event e2(2, "lbl", "desc", 3);

    events.add(e1);
    events.add(e2);

    REQUIRE(events.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(events.erase(1) == 1);
        REQUIRE(events.count() == 1);
        REQUIRE_THROWS_MATCHES(events.at(1), RGException,
                               Message("Invalid ID (1)"));
    }

    SECTION("Bad ID")
    {
        REQUIRE_FALSE(events.erase(3));
        REQUIRE(events.count() == 2);
    }
}

TEST_CASE("Edit an Event", "[Events]")
{
    RotaData<Event> events;
    Event e1(1, "label", "description", 1);
    Event e2(2, "lbl", "desc", 3);

    events.add(e1);
    events.add(e2);

    REQUIRE(events.count() == 2);

    SECTION("Edit Good ID")
    {
        Event e = events.at(1);

        e.set_label("New Label");
        events.update(1, e);

        Event w = events.at(1);
        REQUIRE(w.get_label() == "New Label");
    }

    SECTION("Edit Bad ID")
    {
        Event e3(3, "Event", "A description", 2);

        REQUIRE_THROWS_MATCHES(events.update(3, e3), RGException,
                               Message("Invalid ID (3)"));

        REQUIRE(events.count() == 2);
    }
}
