#include "event_system.h"

Heap<Event> hp([](Event& e1, Event& e2){return e1.time < e2.time;});
float curTime = 0.0f;

void Schedule(int id, float waitTime, std::function<void()> event) {
    Event e(id, curTime + waitTime, event);
    hp.insert(e);
}

void Unschedule(int id) {
    auto f = [id](Event& e) {
        return e.id == id;
    };

    hp.remove(f);
}

void UpdateEventSystem() {
    curTime += GetFrameTime();

    while(!hp.empty() && hp.top().time <= curTime) {
        Event topEvent = hp.pop();
        topEvent.event();
    };
}

void ClearEventSystem() {
    hp.clear();
    curTime = 0.0f;
}