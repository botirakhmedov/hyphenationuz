#include <catch2/catch_test_macros.hpp>

#include "transform_logic.h"

TEST_CASE("syllable")
{
    transform_logic tl;
    //tl.word_to_letters("O‘ma’rifiy");
    REQUIRE(tl.word_to_syllable("adabiy") == "a-da-biy");
    // REQUIRE(summing(1, 0) == 1);
}

TEST_CASE("branch1")
{
    // REQUIRE(fn_branch(true, false) == 0);
    // REQUIRE(fn_branch(true, true) == 0);
    // REQUIRE(fn_branch(false, true) == 0);
    // REQUIRE(fn_branch(false, false) == 1);
}
