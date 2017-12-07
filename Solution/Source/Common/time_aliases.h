#pragma once

#include <chrono>

using Clock = std::chrono::system_clock;
using TimePoint = Clock::time_point;
using Duration = Clock::duration;
using Seconds = std::chrono::seconds;
using Milliseconds = std::chrono::milliseconds;

namespace TimeUnit
{

using ns = std::chrono::nanoseconds;
using us = std::chrono::microseconds;
using ms = std::chrono::milliseconds;
using s = std::chrono::seconds;

}