#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "volunteer.h"
#include "volunteers.h"

TEST(Volunteers, NoDuplicates)
{
    Volunteer v(1, "First name", "Last name", "home", "mobile", "email");

    Volunteers vol;

    vol.add(v);
    vol.add(v);

    EXPECT_EQ(vol.count(), 1);
}

TEST(Volunteers, Save)
{
    Volunteer v(1, "First", "Last", "Home", "Mobile", "Email");
    Volunteer v2(2, "Christian", "Surname", "One", "Two", "m@p");

    Volunteers vol;
    vol.add(v);
    vol.add(v2);

    std::ostringstream out;
    vol.save(out);

}
