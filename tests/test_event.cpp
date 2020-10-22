#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "event.h"

TEST(Event, ToJson)
{
    Event a(1, "label", "description", 2);

    nlohmann::json expected
    {
        {"id", 1},
        {"label", "label"},
        {"description", "description"},
        {"volsNeeded", 2}
    };

    nlohmann::json j;
    a.to_json(j);

    EXPECT_EQ(j, expected);
}
