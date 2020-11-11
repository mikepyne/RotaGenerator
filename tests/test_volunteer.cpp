#include <nlohmann/json.hpp>

#include "test_volunteer.h"

TEST_F(TestVolunteer, Comparison)
{
    Volunteer a(1, "First", "Last", "Home", "Mobile", "Email");
    Volunteer b(2, "First", "Last", "Home", "Mobile", "Email");

    Volunteer c(3, "Forename", "Surname", "Home", "Mobile", "Email");

    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST_F(TestVolunteer, ToJson)
{
    v = Volunteer(1, "First", "Last", "Home", "Mobile", "Email");

    nlohmann::json expected
    {
        {"id", 1},
        {"firstName", "First"},
        {"lastName", "Last"},
        {"homePhone", "Home"},
        {"mobilePhone", "Mobile"},
        {"email", "Email"}
    };

    nlohmann::json j;
    v.to_json(j);

    EXPECT_EQ(j, expected);
}

TEST_F(TestVolunteer, FromJson)
{
    nlohmann::json from
    {
        {"id", 1},
        {"firstName", "First"},
        {"lastName", "Last"},
        {"homePhone", "Home"},
        {"mobilePhone", "Mobile"},
        {"email", "Email"},
    };

    Volunteer expected(1, "First", "Last", "Home", "Mobile", "Email");

    v.from_json(from);

    EXPECT_EQ(v.get_id(), 1);
    EXPECT_EQ(v, expected);
}
