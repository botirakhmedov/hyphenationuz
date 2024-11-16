#include "transform_logic.h"
#include "interface.h"

void transform_logic::test()
{
    std::shared_ptr<repository> repo = std::make_shared<repository>();
    repo->test();
}