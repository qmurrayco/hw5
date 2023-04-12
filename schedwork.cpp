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
static const Worker_T INVALID_ID = (unsigned int)-1;
bool satisfy(const AvailabilityMatrix& avail, DailySchedule& schedM, int day, int shift, map<Worker_T, int>& load);
void buildSched(DailySchedule& sched, int d, int n, int day);

// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    //cout << "inside " << avail.size() << endl;
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    map<Worker_T, int> l;

    buildSched(sched, dailyNeed, avail.size(), 0);
    //cout << "past build" << endl;
    for(Worker_T worker = 0; worker < avail[0].size(); worker++){
        l.insert({worker, maxShifts});
    }


    return satisfy(avail, sched, 0, 0, l);

}

bool satisfy(const AvailabilityMatrix& avail, DailySchedule& sched, int day, int shift, map<Worker_T, int>& load){
    if(day > sched.size()-1){
        return true;
    }
    else if(shift > sched[0].size()-1){
        return satisfy(avail, sched, day + 1, 0, load);
    }

    else{
        for(Worker_T worker = 0; worker < avail[0].size(); worker++){
            int remaining = load[worker];
            if(remaining > 0){
                if(avail[day][worker]){
                    sched[day][shift] = worker;
                    load[worker] = (remaining - 1);
                    if(satisfy(avail, sched, day, shift + 1, load)){
                        return true;
                    }
                    load[worker] = (remaining);
                    sched[day][shift] = INVALID_ID; 
                }
            }
        }
        return false;
    }
}

void buildSched(DailySchedule& sched, int d, int n, int day){
    if(day < n){
        vector<Worker_T> newDay;
        sched.push_back(newDay);
        for(int i = 0; i < d; i++){
            sched[day].push_back(INVALID_ID);
        }
        buildSched(sched, d, n, day+1);
    }
}