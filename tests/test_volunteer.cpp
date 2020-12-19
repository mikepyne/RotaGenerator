#include <nlohmann/json.hpp>

#include "test_volunteer.h"


TEST_F(TestVolunteer, Comparison)
{
    Volunteer a("First", "Last", "Home", "Mobile", "Email");
    Volunteer b("First", "Last", "Home", "Mobile", "Email");

    Volunteer c("Forename", "Surname", "Home", "Mobile", "Email");

    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST_F(TestVolunteer, ToJson)
{
    v = Volunteer("First", "Last", "Home", "Mobile", "Email");

    nlohmann::json expected {
        {"email", "Email"},
        {"firstName", "First"},
        {"lastName", "Last"},
        {"phoneHome", "Home"},
        {"phoneMobile", "Mobile"},
    };

    nlohmann::json j = v;
    EXPECT_EQ(j, expected);
}

TEST_F(TestVolunteer, FromJson)
{
    std::string expected_id {"1"};
    nlohmann::json from {
        {"firstName", "First"},
        {"lastName", "Last"},
        {"phoneHome", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"}
    };

    Volunteer expected("First", "Last", "Home", "Mobile", "Email");

    v = from;
    EXPECT_EQ(v, expected);
}

TEST_F(TestVolunteer, ConstuctFromJson)
{
    nlohmann::json from {
        {"firstName", "First"},
        {"lastName", "Last"},
        {"phoneHome", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"},
    };

    Volunteer expected("First", "Last", "Home", "Mobile", "Email");
    v = Volunteer(from);

    EXPECT_EQ(expected, v);
}

TEST_F(TestVolunteer, AssignFromJson)
{
    nlohmann::json from {
        {"firstName", "First"},
        {"lastName", "Last"},
        {"phoneHome", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"},
    };

    Volunteer expected("First", "Last", "Home", "Mobile", "Email");
    v = from;

    EXPECT_EQ(expected, v);
}

TEST_F(TestVolunteer, ConstructFromJsonBadKey)
{
    nlohmann::json from {
        {"firstName", "First"},
        {"lastName", "Last"},
        {"homePhone", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"},
    };
    EXPECT_THROW((Volunteer(from)), nlohmann::json::out_of_range);
}

TEST_F(TestVolunteer, AssignFromJsonBadKey)
{
    nlohmann::json from {
        {"firstName", "First"},
        {"lastName", "Last"},
        {"homePhone", "Home"},
        {"phoneMobile", "Mobile"},
        {"email", "Email"},
    };
    EXPECT_THROW(v = from, nlohmann::json::out_of_range);
}
