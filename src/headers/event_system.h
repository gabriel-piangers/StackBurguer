#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "heap.h"
#include "constants.h"

struct Event {
    int id;
    float time;
    std::function<void()> event;

    Event(): time(0.0f) {}

    Event(int _id, float _time, std::function<void()> _event): id(_id), time(_time), event(_event) {}
};

// Exports
void Schedule(int id, float waitTime, std::function<void()> event);
void Unschedule(int id);
void UpdateEventSystem();
void ClearEventSystem();


#endif