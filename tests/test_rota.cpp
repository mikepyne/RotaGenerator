#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>
#include <fmt/core.h>

#include "test_rota.h"

using namespace rg;

TEST_CASE("Compare Rota", "[Rota]")
{
    Rota a {1, "label", "description", {1, 2}};
    Rota b {2, "label", "description", {1, 2}};
    Rota c {3, "NotLabel", "Mismatched description", {3, 4}};

    REQUIRE(a == b);
    REQUIRE(a != c);
    REQUIRE_FALSE(a == c);
    REQUIRE_FALSE(a != b);
}

TEST_CASE("Rota to Json", "[Rota]")
{
    Rota           r {1, "Label", "Nice description", {1, 2}};
    nlohmann::json expected {{"id", 1},
                             {"label", "Label"},
                             {"description", "Nice description"},
                             {"events", {1, 2}}};

    nlohmann::json j = r;
    REQUIRE(j == expected);
}

TEST_CASE("Rota From Json", "[Rota]")
{
    nlohmann::json from {{"id", 1},
                         {"label", "label"},
                         {"description", "description"},
                         {"events", {1, 2}}};

    Rota r;
    SECTION("Assign") { r = from; }

    SECTION("Construct") { r = Rota(from); }

    CHECK(r.get_id() == 1);
    CHECK(r.get_label() == "label");
    CHECK(r.get_description() == "description");
}

TEST_CASE("Missing rota elements", "[Rota]")
{
    nlohmann::json from {{"id", 1},
                         {"label", "Label"},
                         {"description", "Description"}};

    Rota r;
    SECTION("Construct")
    {
        REQUIRE_THROWS_AS(r = from, nlohmann::json::out_of_range);
    }

    SECTION("Assign") { REQUIRE_THROWS_AS(r = from, nlohmann::json::out_of_range); }
}
