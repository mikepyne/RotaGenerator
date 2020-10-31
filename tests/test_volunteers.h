#ifndef TEST_VOLUNTEERS_H
#define TEST_VOLUNTEERS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "volunteer.h"
#include "volunteers.h"


class TestVolunteers : public ::testing::Test
{

protected:
    Volunteers vols;
    Volunteer v1;
    Volunteer v2;

    void SetUp() override;
};

#endif // TEST_VOLUNTEERS_H
