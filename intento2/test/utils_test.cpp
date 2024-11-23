#include <gtest/gtest.h>
#include "../include/utils.h"

TEST(obtein_ip, EXPECT_EQ)
{
    EXPECT_EQ("192.168.0.2", obtenerIP()); // interiores
    EXPECT_EQ("192.168.1.137", obtenerIP()); // exteriores
}

TEST(STRINGHANDLER, EXPECT_EQ)
{
    StringHandler sh;
    EXPECT_TRUE(sh.isInSameNetwork("192.168.1.44"))
}
