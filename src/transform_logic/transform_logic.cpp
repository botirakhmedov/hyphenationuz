#include "transform_logic.h"
#include "interface.h"

void transform_logic::test()
{
    std::shared_ptr<repository> repo = std::make_shared<repository>();
    repo->test();
}

std::string transform_logic::parse_to_syllable(std::string inp_word)
{
    return std::string();
}
