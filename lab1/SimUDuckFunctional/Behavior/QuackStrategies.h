#include <iostream>
#include <functional>
#pragma once

std::function<void()> GetCommonQuackFunction();

std::function<void()> GetMuteQuackFunction();

std::function<void()> GetSqueakFunction();