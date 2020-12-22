#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include "test_event.h"

TEST_CASE("Comparing Events", "[Events]")
{
    Event a {1, "label", "description", 2};
    Event b {2, "label", "description", 2};
    Event c {1, "lbl", "desc", 1};

    CHECK(a == b);
    CHECK_FALSE(a == c);
}

TEST_CASE("Event to Json", "[Events]")
{
    Event a {1, "label", "description", 2};

    nlohmann::json expected
    {
        {"id", 1},
        {"label", "label"},
        {"description", "description"},
        {"volsNeeded", 2}
    };

    nlohmann::json j;
    a.to_json(j);

    REQUIRE(j == expected);
}

TEST_CASE("Event from Json", "[Events]")
{
    nlohmann::json from
    {
        {"id", 1},
        {"label", "label"},
        {"description", "description"},
        {"volsNeeded", 2}
    };

    Event a;
    a.from_json(from);

    CHECK(a.get_id() == 1);
    CHECK(a.get_label() == "label");
    CHECK(a.get_description() == "description");
    CHECK(a.get_vols_needed() == 2);
}
