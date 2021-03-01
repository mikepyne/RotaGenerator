#include <catch2/catch.hpp>
#include <nlohmann/json.hpp>

#include "rgexception.h"
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

//TEST_CASE("Add event", "[RotaDetails]")
//{
//    RotaDetails rd;

//    SECTION("Add event")
//    {
//        std::vector<int> vols {};
//        REQUIRE_NOTHROW(rd.add_event(1));
//        REQUIRE(rd.get_event(1) == vols);
//    }

//    SECTION("Add duplicate event")
//    {
//        rd.add_event(1);

//        REQUIRE_THROWS_MATCHES(rd.add_event(1), RGException,
//                               "Event 1 already added");
//    }
//}

//TEST_CASE("Add volunteer", "[RotaDetails]")
//{
//    RotaDetails rd;
//    std::vector<int> vol_events {1, 2, 3};

//    SECTION("No events added")
//    {
//        REQUIRE_THROWS_MATCHES(rd.add_volunteer(1, vol_events), RGException,
//                               "No events; add events first");
//    }

//    SECTION("Volunteer with invalid event")
//    {
//        rd.addEvent(1);
//        rd.addEvent(2);

//        REQUIRE_THROWS_MATCHES(rd.addVolunteer(1, vol_events), RGException,
//                               "Error adding volunteer; event ID 3 hasn't been added");
//    }
//}
