#pragma once

#include <chrono>

int date(time_t &zeroTime)
{
    // How many real life seconds it takes for a virtual day to pass
    int dayLength = 5;
    time_t currentTime = time(NULL);
    return ((currentTime - zeroTime) / dayLength);
}
