#pragma once

#include "software/world/world.h"
#include "software/simulated_tests/validation/validation_function.h"

void oneMeterFromBall(std::shared_ptr<World> world_ptr, ValidationCoroutine::push_type& yield);
