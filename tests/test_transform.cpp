#include <catch2/catch_test_macros.hpp>

#include "transform_logic.h"
#include "word_extractor.h"

TEST_CASE("syllable")
{
    transform_logic tl;
    //tl.word_to_letters("O‘ma’rifiy");
    std::string source {"O‘ma’rifiy"};
    tl.replace_all(source, "‘","`");
    tl.replace_all(source, "’","'");
    REQUIRE(source == "O`ma'rifiy");
}

TEST_CASE("word_extractor")
{
    SECTION( "Get clean word" ) {
        REQUIRE(word_extractor::get_clean_word(" ()[]/O‘ma’rifiy (sosd)") == "O‘ma’rifiy");
        REQUIRE(word_extractor::get_clean_word(" O‘ma’ri-fiy (sosd)") == "O‘ma’ri-fiy");
        REQUIRE(word_extractor::get_clean_word(" -O‘ma’rifiy,: (sosd)") == "O‘ma’rifiy");
    }

    SECTION( "Get ASCII word" ) {
        REQUIRE(word_extractor::convert_to_one_letter_ascii("O‘ma’rifiy") == "0ma'rifiy");
        REQUIRE(word_extractor::convert_to_one_letter_ascii("Chang") == "cang");
        REQUIRE(word_extractor::convert_to_one_letter_ascii("tasdig‘i") == "tasdi9i");
        REQUIRE(word_extractor::convert_to_one_letter_ascii("tasdig`i") == "tasdi9i");
        REQUIRE(word_extractor::convert_to_one_letter_ascii("toshqin") == "towqin");
    }
    
}