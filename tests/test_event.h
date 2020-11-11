#ifndef TEST_EVENT_H
#define TEST_EVENT_H

#include <gtest/gtest.h>

#include "event.h"

class TestEvent : public ::testing::Test
{
protected:
    Event e;
};

#endif // TEST_EVENT_H
