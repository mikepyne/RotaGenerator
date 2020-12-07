#include <string_view>

#include "test_volunteers.h"


void TestVolunteers::SetUp()
{
    v1 = Volunteer("First name", "Last name", "home", "mobile", "email");
    v2 = Volunteer("Christian", "Surname", "One", "Two", "m@p");
}

TEST_F(TestVolunteers, NoDuplicates)
{
    EXPECT_TRUE(vols.add(v1));
    EXPECT_FALSE(vols.add(v1));
    EXPECT_EQ(vols.count(), 1);
}

TEST_F(TestVolunteers, Save)
{
    std::stringstream expected;
    expected << R"({"1":{"email":"email","firstName":"First Name",)"
             << R"("homePhone":"home","lastName":"Last name",)"
             << R"("mobilePhone":"mobile},{"2":{"email":"m@p","firstName":"Christian",)"
             << R"("homePhone":"One","lastName":"Surname","mobilePhone":"Two"}})"
             << std::endl;

    vols.add(v1);
    vols.add(v2);

    std::stringstream out;
    vols.save(out);

    EXPECT_EQ(out.str(), expected.str());
}

TEST_F(TestVolunteers, EmptyLoad)
{
    std::stringstream in;

    EXPECT_NO_THROW(vols.load(in));
    EXPECT_EQ(vols.count(), 0);
}

TEST_F(TestVolunteers, Load)
{
    std::stringstream in;
    in << R"({"1": {"email":"email","firstName":"First Name",)"
       << R"("homePhone":"home","lastName":"Last name",)"
       << R"("mobilePhone":"mobile},"2": {"email":"m@p","firstName":"Christian",)"
       << R"("homePhone":"One","lastName":"Surname",)"
       << R"("mobilePhone":"Two"}})";

    EXPECT_NO_THROW(vols.load(in));
    EXPECT_EQ(vols.count(), 2);
}
