#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "test_event.h"

TEST_F(TestEvent, Comparison)
{
    e = Event(1, "label", "description", 2);
    Event b {2, "label", "description", 2};

    Event c {1, "lbl", "desc", 1};

    EXPECT_EQ(e, b);
    EXPECT_NE(e, c);
}

TEST_F(TestEvent, ToJson)
{
    e = Event(1, "label", "description", 2);

    nlohmann::json expected
    {
        {"id", 1},
        {"label", "label"},
        {"description", "description"},
        {"volsNeeded", 2}
    };

    nlohmann::json j;
    e.to_json(j);

    EXPECT_EQ(j, expected);
}

TEST_F(TestEvent, FromJson)
{
    nlohmann::json from
    {
        {"id", 1},
        {"label", "label"},
        {"description", "description"},
        {"volsNeeded", 2}
    };

    e.from_json(from);

    EXPECT_EQ(e.get_id(), 1);
    EXPECT_EQ(e.get_label(), "label");
    EXPECT_EQ(e.get_description(), "description");
    EXPECT_EQ(e.get_vols_needed(), 2);
}
