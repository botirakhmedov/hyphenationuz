#pragma once
#include <memory>
#include "data_repository.h"

std::shared_ptr<repository> create_repository()
{
    std::shared_ptr<repository> ret_val = std::make_shared<repository>();
    return ret_val; 
}