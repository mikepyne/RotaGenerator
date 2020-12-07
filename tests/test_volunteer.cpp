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

    std::string dump = j.dump();
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
//    Volunteer::from_json(from, v);

    EXPECT_EQ(v, expected);
}
