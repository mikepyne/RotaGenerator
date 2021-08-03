#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>

#include "rgexception.h"
#include "test_rota.h"

using Catch::Matchers::Message;
using nlohmann::json;
using namespace rg;

TEST_CASE("Compare Rota", "[Rota]")
{
    Rota a {1, "label", "description", {1, 2}};
    Rota b {2, "label", "description", {1, 2}};
    Rota c {3, "NotLabel", "Mismatched description", {3, 4}};

    CHECK(a == b);
    CHECK(a != c);
    CHECK_FALSE(a == c);
    CHECK_FALSE(a != b);
}

TEST_CASE("Rota to Json", "[Rota]")
{
    nlohmann::json expected;
    nlohmann::json j;

    SECTION("Valid rota")
    {
        Rota r {1, "Label", "Nice description", {1, 2}};
        expected = {{"id", 1},
                    {"label", "Label"},
                    {"description", "Nice description"},
                    {"events", {1, 2}}};

        j = r;
        REQUIRE(j == expected);
    }

    SECTION("No events")
    {
        Rota r {1, "Label", "Nice description", {}};
        expected = {{"id", 1},
                    {"label", "Label"},
                    {"description", "Nice description"},
                    {"events", json::array()}};

        j = r;
        REQUIRE(j == expected);
    }
}

TEST_CASE("Rota From Json", "[Rota]")
{
    nlohmann::json from {{"id", 1},
                         {"label", "label"},
                         {"description", "description"},
                         {"events", {1, 2}}};

    Rota r;
    Rota rb;
    SECTION("Assign")
    {
        r  = from;
        rb = r;
        CHECK(r.get_id() == 1);
        CHECK(r.get_label() == "label");
        CHECK(r.get_description() == "description");
        CHECK(r.get_events() == std::vector<int> {1, 2});

        CHECK(r == rb);
    }

    SECTION("Construct")
    {
        r = Rota(from);
        CHECK(r.get_id() == 1);
        CHECK(r.get_label() == "label");
        CHECK(r.get_description() == "description");
        CHECK(r.get_events() == std::vector<int> {1, 2});
    }
}

TEST_CASE("Missing rota events", "[Rota]")
{
    nlohmann::json from {{"id", 1},
                         {"label", "Label"},
                         {"description", "Description"}};

    Rota r;
    SECTION("Construct")
    {
        REQUIRE_THROWS_MATCHES(Rota(from),
                               RGException,
                               Message("Key events is missing from ID 1"));
    }

    SECTION("Assign")
    {
        REQUIRE_THROWS_MATCHES(r = from,
                               RGException,
                               Message("Key events is missing from ID 1"));
    }
}

TEST_CASE("Adding events to a rota", "[Rota]")
{
    Rota             r(1, "Label", "A rota", {1, 2});
    std::vector<int> to_add;

    SECTION("No duplicates")
    {
        to_add = {3, 4};
        REQUIRE_NOTHROW(r.add_events(to_add));
        REQUIRE(r.get_events() == std::vector<int> {1, 2, 3, 4});
    }

    SECTION("Duplicates")
    {
        to_add = {2, 3};
        REQUIRE_NOTHROW(r.add_events(to_add));
        REQUIRE(r.get_events() == std::vector<int> {1, 2, 3});
    }

    SECTION("High to low")
    {
        Rota r2(1, "Label", "Description", {9, 8});
        to_add = {7, 6};
        REQUIRE_NOTHROW(r2.add_events(to_add));
        REQUIRE(r2.get_events() == std::vector<int> {6, 7, 8, 9});
    }

    SECTION("Opposite order")
    {
        to_add = {2, 1};

        REQUIRE_NOTHROW(r.add_events(to_add));
        REQUIRE(r.get_events() == std::vector<int> {1, 2});
    }
}

TEST_CASE("Removing events from a rota", "[Rota]")
{
    Rota             r(1, "Label", "A rota", {1, 2, 3});
    std::vector<int> to_remove;

    SECTION("Remove single event")
    {
        to_remove = {1};
        REQUIRE_NOTHROW(r.remove_events(to_remove));
        REQUIRE(r.get_events() == std::vector<int> {2, 3});
    }

    SECTION("Remove multiple events")
    {
        to_remove = {1, 3};
        REQUIRE_NOTHROW(r.remove_events(to_remove));
        REQUIRE(r.get_events() == std::vector<int> {2});
    }
}
