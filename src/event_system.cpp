#include "event_system.h"

using namespace std;

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
    if(IsKeyPressed(KEY_L)) { // Debugging
        cout << "\n--- Event System ---\n";
        cout << "Size: " << hp.size << "\n"; 
    }

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