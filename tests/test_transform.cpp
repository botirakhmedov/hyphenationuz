#include <catch2/catch_test_macros.hpp>

#include "transform_logic.h"

TEST_CASE("syllable")
{
    transform_logic tl;
    //tl.word_to_letters("O‘ma’rifiy");
    std::string source {"O‘ma’rifiy"};
    tl.replace_all(source, "‘","`");
    tl.replace_all(source, "’","'");
    REQUIRE(source == "O`ma'rifiy");
    // REQUIRE(summing(1, 0) == 1);
}
