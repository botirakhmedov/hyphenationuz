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
    test_input_data{"O‘ma’rifiy", "0ma'rifiy", "0-ma'-ri-fiy", "0ma'-ri-fiy"},
    test_input_data{"idish", "idiw", "i-diw", "idiw"}
};

// class AnalyzeParameterizedTest : public testing::TestWithParam<test_input_data> {
//     public:
//         core::transform tr_object;
// };

TEST(WordTransformationTest, AnalyzeWord)
{
    for(const auto& in_item: inp_data_vector)
    {
        core::transform tr;
        auto resultval = tr.analyze_word(in_item.input); 
        EXPECT_FALSE(resultval.has_error());
        EXPECT_EQ(in_item.out_word, resultval.data().target_word);
        EXPECT_EQ(in_item.out_syllable, resultval.data().syllable);
        EXPECT_EQ(in_item.out_hyphenation, resultval.data().hyphenation);
    }
}

TEST(WordTransformationTest, SplitWord)
{
    core::transform tr;
    std::string in_text = "If you find    yourself writing two";
    std::vector<std::string> result{"If", "you", "find", "yourself", "writing", "two"};
    auto resultval = tr.string_to_words(in_text);
    EXPECT_EQ(result.size(), resultval.size());
    EXPECT_TRUE(std::equal(std::begin(resultval), std::end(resultval), std::begin(result), std::end(result))); 
}

// TEST_P(AnalyzeParameterizedTest, AnalyzeWordTest)
// {
//     auto in_item = GetParam();
//     auto resultval = tr_object.analyze_word(in_item.input); 
//     EXPECT_FALSE(resultval.has_error());
//     EXPECT_EQ(in_item.out_word, resultval.data().target_word);
//     EXPECT_EQ(in_item.out_syllable, resultval.data().syllable);
//     EXPECT_EQ(in_item.out_hyphenation, resultval.data().hyphenation);
// }

// INSTANTIATE_TEST_SUITE_P(WordValues, AnalyzeParameterizedTest, testing::ValuesIn(inp_data_vector));