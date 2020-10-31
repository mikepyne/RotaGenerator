#include <string_view>

#include "test_volunteers.h"

void TestVolunteers::SetUp()
{
    v1 = Volunteer(1, "First name", "Last name", "home", "mobile", "email");
    v2 = Volunteer(2, "Christian", "Surname", "One", "Two", "m@p");
}

TEST_F(TestVolunteers, NoDuplicates)
{
    vols.add(v1);
    vols.add(v1);

    EXPECT_EQ(vols.count(), 1);
}

TEST_F(TestVolunteers, Save)
{
    std::stringstream expected;
    expected << R"({"email":"m@p","firstName":"Christian","homePhone":"One",)"
             << R"("id":2,"lastName":"Surname","mobilePhone":"Two"})"
             << std::endl;

    vols.add(v1);
    vols.add(v2);

    std::stringstream out;
    vols.save(out);

    EXPECT_EQ(out.str(), expected.str());
}
