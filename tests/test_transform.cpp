#include <gmock/gmock.h>
#include "transform.h"

struct test_input_data{
    std::string input;
    std::string out_word;
    std::string out_syllable;
    std::string out_hyphenation;
};

std::vector<test_input_data> inp_data_vector {
    test_input_data{"alangali", "alangali", "a-lan-ga-li", "alan-ga-li"},
    test_input_data{"O‘ma’rifiy", "0ma'rifiy", "0-ma'-ri-fiy", "0ma'-ri-fiy"}
};

TEST(WordTransformationTest, AnalyzeWord)
{
    //test_input_data test_input = GetParam();
    
    for(const auto& in_item: inp_data_vector)
    {
        auto resultval = transform::analyze_word(in_item.input); 
        EXPECT_FALSE(resultval.has_error());
        EXPECT_EQ(in_item.out_word, resultval.data().target_word);
        EXPECT_EQ(in_item.out_syllable, resultval.data().syllable);
        EXPECT_EQ(in_item.out_hyphenation, resultval.data().hyphenation);
    }
    
}
