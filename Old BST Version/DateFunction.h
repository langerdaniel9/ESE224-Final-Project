#pragma once

#include <chrono>

/***
 * @brief Gets number of virtual days that have passed
 * @param zeroTime time_t at which the user first logged in
 * @return Number of virtual days as an int
 */
int date(time_t &zeroTime)
{
    // How many real life seconds it takes for a virtual day to pass
    int dayLength = 5;
    time_t currentTime = time(NULL);
    return ((currentTime - zeroTime) / dayLength);
}
