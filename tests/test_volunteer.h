#ifndef TEST_VOLUNTEER_H
#define TEST_VOLUNTEER_H

#include <gtest/gtest.h>

#include "volunteer.h"

class TestVolunteer : public ::testing::Test
{
protected:
    Volunteer v;
};

#endif // TEST_VOLUNTEER_H
