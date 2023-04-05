#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day,
    int col
);

bool hasMaxShifts(Worker_T id, const DailySchedule& sched, const size_t maxShifts, int i, int j, int cnt);


// Add your implementation of schedule() and other helper functions here

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
    // Add your code below

    // Initialize empty schedule
    for (int i = 0; i < (int) avail.size(); i++) {
        sched.push_back(vector<Worker_T>());
    }
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0);



}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day,
    int col
)
{
    // Base case????
    if (day >= (int) avail.size()) return true;

    // Set variables for next iteration
    int d, c;
    if (col == (int) dailyNeed - 1) {
        d = day + 1;
        c = 0;
    } else {
        d = day;
        c = col + 1;
    }

    // Backtracking search
    for (Worker_T i = 0; i < avail[day].size(); i++) {
        // If worker is available on this day
        if(avail[day][i] == 1 && find(sched[day].begin(), sched[day].end(), i) == sched[day].end()) {
            // Try putting the worker i in this slot
            sched[day].push_back(i);
            // If worker does not have max shifts and shifts are needed to be filled
            if (sched[day].size() <= dailyNeed && !(hasMaxShifts(i, sched, maxShifts, 0, 0, 0))) {
                bool verify = scheduleHelper(avail, dailyNeed, maxShifts, sched, d, c);
                if (verify) return true;
            }
            sched[day].pop_back();
        }
    }
    return false;
}

bool hasMaxShifts(Worker_T id, const DailySchedule& sched, const size_t maxShifts, int i, int j, int cnt)
{
    if (sched[i][j] == id) cnt++;
    if (cnt > (int) maxShifts) return true;

    if (i == (int) sched.size() - 1 && j == (int) sched[i].size() - 1) {
        return false;
    } else if (j == (int) sched[i].size() - 1) {
        if (sched[i+1].size() == 0) return false;
        return hasMaxShifts(id, sched, maxShifts, i+1, 0, cnt);
    } else {
        return hasMaxShifts(id, sched, maxShifts, i, j+1, cnt);
    } 
}