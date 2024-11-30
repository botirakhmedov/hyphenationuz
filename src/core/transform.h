#pragma once
#include <string>
#include <iostream>
#include "commondto.h"
#include "result.h"

namespace transform{
    result<dto::word_unit> analyze_word(const std::string& inp_word);
}
