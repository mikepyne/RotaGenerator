#include <nlohmann/json.hpp>

#include "test_volunteer.h"


TEST_F(TestVolunteer, Comparison)
{
    Volunteer a("1", "First", "Last", "Home", "Mobile", "Email");
    Volunteer b("2", "First", "Last", "Home", "Mobile", "Email");

    Volunteer c("3", "Forename", "Surname", "Home", "Mobile", "Email");

    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
}

TEST_F(TestVolunteer, ToJson)
{
    v = Volunteer("1", "First", "Last", "Home", "Mobile", "Email");

    nlohmann::json expected {
        {"1", {
            {"firstName", "First"},
            {"lastName", "Last"},
            {"homePhone", "Home"},
            {"mobilePhone", "Mobile"},
            {"email", "Email"}
        }}
    };

    nlohmann::json j = v.to_json();

    std::string dump = j.dump();
    EXPECT_EQ(j, expected);
}

TEST_F(TestVolunteer, FromJson)
{
    std::string expected_id {"1"};
    nlohmann::json from {
        {"1", {
            {"firstName", "First"},
            {"lastName", "Last"},
            {"homePhone", "Home"},
            {"mobilePhone", "Mobile"},
            {"email", "Email"}
        }}
    };

    Volunteer expected(expected_id, "First", "Last", "Home", "Mobile", "Email");

    v.from_json(from);

    EXPECT_EQ(v.get_id(), expected_id);
    EXPECT_EQ(v, expected);
}
