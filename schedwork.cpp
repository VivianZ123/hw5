#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
typedef unsigned int Worker_T;
static const Worker_T INVALID_ID = static_cast<unsigned int>(-1);

bool scheduleHelper(const vector<vector<bool>>& avail, size_t dailyNeed, size_t maxShifts, 
                    vector<vector<Worker_T>>& sched, vector<int>& shifts, size_t dayIndex, size_t shiftIndex);

bool isValid(const vector<vector<bool>>& avail, size_t maxShifts, const vector<vector<Worker_T>>& sched, 
             const vector<int>& shifts, size_t row, size_t col);

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<int> shifts(avail[0].size(), 0);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}
bool scheduleHelper(
    const vector<vector<bool>>& avail, 
    size_t dailyNeed, 
    size_t maxShifts, 
    vector<vector<Worker_T>>& sched, 
    vector<int>& shifts, 
    size_t dayIndex, 
    size_t shiftIndex
) {
    if (dayIndex == avail.size()) {
        return true;
    }

    if (shiftIndex == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, dayIndex + 1, 0);
    }

    for (Worker_T worker = 0; worker < avail[dayIndex].size(); ++worker) {
        sched[dayIndex][shiftIndex] = worker;
        shifts[worker]++;

        if (isValid(avail, maxShifts, sched, shifts, dayIndex, shiftIndex)) {
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, dayIndex, shiftIndex + 1)) {
                return true;
            }
        }
        sched[dayIndex][shiftIndex] = INVALID_ID;
        shifts[worker]--;
    }

    return false;
}
bool isValid(
    const vector<vector<bool>>& avail, 
    size_t maxShifts, 
    const vector<vector<Worker_T>>& sched, 
    const vector<int>& shifts, 
    size_t row, 
    size_t col
) {
    Worker_T worker = sched[row][col];
    for (size_t i = 0; i < col; ++i) {
        if (sched[row][i] == worker) {
            return false;
        }
    }
    return avail[row][worker] && static_cast<size_t>(shifts[worker]) <= maxShifts;
}