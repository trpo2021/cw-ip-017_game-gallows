#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch.hpp"

TEST_CASE("2 + 2 = 4")
{
    REQUIRE(2 + 2  == 4);
}
