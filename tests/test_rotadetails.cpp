#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include "test_rotadetails.h"

TEST_CASE("Compare Rota Details", "[RotaDetails]")
{
    RotaDetails a {1, "Label"};
    RotaDetails b {2, "Label"};
    RotaDetails c {3, "A Label"};

    CHECK(a == b);
    CHECK(a != c);
    CHECK_FALSE(a == c);
    CHECK_FALSE(a != b);
}

TEST_CASE("Rota Details to Json", "[RotaDetails]")
{
    RotaDetails rd {1, "Label"};
    nlohmann::json expected {
        {"id", 1},
        {"label", "Label"},
    };

    nlohmann::json j = rd;
    REQUIRE(j == expected);
}

TEST_CASE("Rota Details from Json", "[RotaDetails]")
{
    nlohmann::json from {
        {"id", 1},
        {"label", "The label"}
    };

    RotaDetails rd;

    SECTION("Assign")
    {
        rd = from;
    }

    SECTION("Construct")
    {
        rd = RotaDetails(from);
    }

    REQUIRE(rd.get_id() == 1);
    REQUIRE(rd.get_label() == "The label");
}

TEST_CASE("Rota Details with a bad key", "RotaDetails]")
{
    // With lable as a deliberately bad key
    nlohmann::json from {
        {"id", 1},
        {"lable", "The label"}
    };

    SECTION("Construct")
    {
        REQUIRE_THROWS_AS(RotaDetails(from), nlohmann::json::out_of_range);
    }

    SECTION("Assign")
    {
        RotaDetails rd;
        REQUIRE_THROWS_AS(rd = from, nlohmann::json::out_of_range);
    }
}
