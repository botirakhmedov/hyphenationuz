#include <gtest/gtest.h>

#include "transform_logic.h"
#include "word_extractor.h"

TEST(WordExtractortest, replaceAll)
{
    transform_logic tl;
    //tl.word_to_letters("O‘ma’rifiy");
    std::string source {"O‘ma’rifiy"};
    tl.replace_all(source, "‘","`");
    tl.replace_all(source, "’","'");
    EXPECT_TRUE(source == "O`ma'rifiy");
}

TEST(WordExtractorTest, asciiConversion)
{
    EXPECT_TRUE(word_extractor::get_clean_word(" ()[]/O‘ma’rifiy (sosd)") == "O‘ma’rifiy");
    EXPECT_TRUE(word_extractor::get_clean_word(" O‘ma’ri-fiy (sosd)") == "O‘ma’ri-fiy");
    EXPECT_TRUE(word_extractor::get_clean_word(" -O‘ma’rifiy,: (sosd)") == "O‘ma’rifiy");
    
    EXPECT_TRUE(word_extractor::convert_to_one_letter_ascii("O‘ma’rifiy") == "0ma'rifiy");
    EXPECT_TRUE(word_extractor::convert_to_one_letter_ascii("Chang") == "cang");
    EXPECT_TRUE(word_extractor::convert_to_one_letter_ascii("tasdig‘i") == "tasdi9i");
    EXPECT_TRUE(word_extractor::convert_to_one_letter_ascii("tasdig`i") == "tasdi9i");
    EXPECT_TRUE(word_extractor::convert_to_one_letter_ascii("toshqin") == "towqin");
    
    
}