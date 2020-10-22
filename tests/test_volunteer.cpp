#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "volunteer.h"

TEST(Volunteer, Comparison)
{
    Volunteer a(1, "First", "Last", "Home", "Mobile", "Email");
    Volunteer b(2, "First", "Last", "Home", "Mobile", "Email");

    Volunteer c(3, "Forename", "Surname", "Home", "Mobile", "Email");

    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST(Volunteer, ToJson)
{
    Volunteer a(1, "First", "Last", "Home", "Mobile", "Email");

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
    a.to_json(j);

    EXPECT_EQ(j, expected);
}

TEST(Volunteer, FromJson)
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

    Volunteer a;

    a.from_json(from);

    EXPECT_EQ(a.get_id(), 1);
    EXPECT_EQ(a, expected);
}
