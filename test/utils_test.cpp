#include <gtest/gtest.h>
#include "../lib/utils.h"

TEST(obtein_ip, EXPECT_EQ)
{
    EXPECT_EQ("10.0.2.15", obtenerIP());
}
