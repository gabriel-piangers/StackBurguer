#include "history.h"
#include "dynamic_vector.h"
#include "timer.h"
#include <fstream>

using namespace std;

DynamicVector<Record> history;

void InitHistory(string path = "") {
    Timer timer;
    timer_iniciar(&timer);

    if(path.size() == 0) {
        cout << "[INFO] No history file informed!\n";
        return;
    }

    ifstream file(path);

    if(!file.is_open()) {
        cerr << "[Error] Failed to open history file\n";
        return;
    }

    string name;
    string scoreStr;
    while(getline(file, name)) {
        getline(file, scoreStr);
        float score = stof(scoreStr);
        history.insert((Record) {name, score});
    }

    file.close();
    cout << "InitHistory execution time: " << timer_parar(&timer) << " seconds \n";
}

Record* GetRecords(int n, int page) {
    if(n*page < 0 || n*page >= history.size) return nullptr;
    return &history[page*n];
}

int ItemsInPage(int n, int page) {
    if(n*(page+1) >= history.size) {
        return n;
    }
    return min(n, history.size - (n*page));
}