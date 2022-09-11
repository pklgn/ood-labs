#pragma once
#include <functional>

using count_type = size_t;

std::function<void()> GetFlyWithWingsFunction();

std::function<void()> GetFlyNoWayFunction();

std::function<void()> GetFlyWithRocketPowerFunction();