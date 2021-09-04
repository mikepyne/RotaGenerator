#include <sstream>
#include <catch2/catch.hpp>

#include "test_rotas.h"

using Catch::Matchers::Message;
using namespace rg;

TEST_CASE("Loading rotas", "[Rotas]")
{
    RotaData<MockRota> rotas;
    std::stringstream  in;

    SECTION("Empty rotas")
    {
        REQUIRE_NOTHROW(rotas.load(in));
        CHECK(rotas.count() == 0);
    }

    SECTION("Bad Key")
    {
        in << R"({"data":[{"id":1,"label":"A Label","description":"A Description"}]})";

        REQUIRE_NOTHROW(rotas.load(in));
        CHECK(rotas.count() == 1);
    }

    SECTION("No Duplicates")
    {
        MockRota r1;
        MockRota r2;

        REQUIRE_CALL(r1, get_id()).TIMES(AT_LEAST(1)).RETURN(1);
        REQUIRE_CALL(r2, eq(ANY(MockRota))).RETURN(true);

        REQUIRE(rotas.add(r1) == 1);
        REQUIRE(rotas.add(r2) == -1);

        REQUIRE(rotas.count() == 1);
    }

    SECTION("Bad JSON")
    {
        in << R"({"data: [{"id":1"label":"A Label","description":"A Description"}]})";

        REQUIRE_THROWS_AS(rotas.load(in), rg::LoadError);
    }
}

TEST_CASE("Save rotas", "[Rotas]")
{
    RotaData<MockRota> rotas;
    std::stringstream  expected;
    std::stringstream  out;

    SECTION("Save empty rotas")
    {
        expected << "{}" << std::endl;

        rotas.save(out);
        REQUIRE(out.str() == "null");
    }

    SECTION("Good save")
    {
        expected
            << R"({"data":[{"description":"A Description","events":[1,2],)"
            << R"("id":1,"label":"A Label"},{"description":)"
            << R"("Second description","events":[2],"id":2,"label":"Second label"}]})";

        MockRota r1(1, "A Label", "A Description", {1, 2});
        MockRota r2(3, "Second label", "Second description", {2});

        ALLOW_CALL(r1, get_id()).RETURN(1);
        ALLOW_CALL(r2, get_id()).RETURN(2);
        ALLOW_CALL(r2, eq(ANY(MockRota))).RETURN(false);

        rotas.add(r1);
        rotas.add(r2);
        rotas.save(out);

        REQUIRE(out.str() == expected.str());
    }
}

TEST_CASE("Getting a Rota", "[Rotas]")
{
    RotaData<Rota> rotas;
    Rota           r1(1, "label", "description", {1, 2});
    Rota           r2(2, "lbl", "desc", {2});

    rotas.add(r1);
    rotas.add(r2);

    REQUIRE(rotas.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(rotas.at(1) == r1);
        REQUIRE(rotas.at(2) == r2);
    }

    SECTION("Bad ID")
    {
        REQUIRE_THROWS_MATCHES(rotas.at(3), rg::Invalid, Message("Invalid ID (3)"));
    }
}

TEST_CASE("Deleting a Rota", "[Rotas]")
{
    RotaData<Rota> rotas;
    Rota           r1(1, "label", "description", {1, 2});
    Rota           r2(2, "lbl", "desc", {2});

    rotas.add(r1);
    rotas.add(r2);

    REQUIRE(rotas.count() == 2);

    SECTION("Good ID")
    {
        REQUIRE(rotas.erase(1) == 1);
        REQUIRE(rotas.count() == 1);
        REQUIRE_THROWS_MATCHES(rotas.at(1), RGException, Message("Invalid ID (1)"));
    }

    SECTION("Bad ID")
    {
        REQUIRE_FALSE(rotas.erase(3));
        REQUIRE(rotas.count() == 2);
    }
}

TEST_CASE("Edit a Rota", "[Rotas]")
{
    RotaData<Rota> rotas;
    Rota           r1(1, "label", "description", {1, 2});
    Rota           r2(2, "lbl", "desc", {2});

    rotas.add(r1);
    rotas.add(r2);

    REQUIRE(rotas.count() == 2);

    SECTION("Edit Good ID")
    {
        Rota to_edit = rotas.at(1);

        to_edit.set_label("New Label");
        rotas.update(1, to_edit);

        Rota edited = rotas.at(1);
        REQUIRE(edited.get_label() == "New Label");
    }

    SECTION("Edit Bad ID")
    {
        Rota to_edit(3, "Rota", "A rota", {1, 2});

        REQUIRE_THROWS_MATCHES(rotas.update(3, to_edit),
                               RGException,
                               Message("Invalid ID (3)"));

        REQUIRE(rotas.count() == 2);
    }
}

TEST_CASE("Rotas with no data", "[Rotas]")
{
    RotaData<Rota> rotas;

    REQUIRE(rotas.count() == 0);
}

TEST_CASE("Next ID", "[Rotas]")
{
    RotaData<Rota>    rotas;
    std::stringstream in;

    Rota r2;
    r2.set_label("New Label");
    r2.set_description("A description");
    r2.set_events({1, 2});

    in << R"({"data":[{"id":10,"label":"A Label","description":"A Description")"
          R"(,"events":[1]}]})";

    rotas.load(in);
    CHECK(rotas.count() == 1);

    rotas.add(r2);
    CHECK(rotas.count() == 2);
    REQUIRE(r2.get_id() == 11);

    std::stringstream out;

    rotas.save(out);

    auto expected =
        R"({"data":[{"description":"A Description","events":[1],"id":10,)"
        R"("label":"A Label"},{"description":"A description","events":[1,2],)"
        R"("id":11,"label":"New Label"}]})";

    REQUIRE(out.str() == expected);
}
