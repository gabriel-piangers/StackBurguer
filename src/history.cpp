#include "history.h"
#include "dynamic_vector.h"
#include "timer.h"
#include "ui.h"
#include <fstream>

using namespace std;

DynamicVector<Record> history;
int curPage = 0;
HistoryField selectedField = NONE;
bool sortingAsc = false;


Button noneFieldBtn({0}, "#", []() {
    selectedField = NONE;
    InitHistory("data/historico.txt"); // change later
});
Button nameFieldBtn({0}, "Name", []() {
    selectedField = NAME;
    sortingAsc = !sortingAsc;
    SortRecordsByName(sortingAsc);
});
Button scoreFieldBtn({0}, "Score", []() {
    selectedField = SCORE;
    sortingAsc = !sortingAsc;
    SortRecordsByScore(sortingAsc);
});

Button nextPageBtn({0}, " >> ", []() {curPage++;});
Button prevPageBtn({0}, " << ", []() {curPage--;});

void InitHistory(string path = "") {
    const float headerHeight = RECORD_FONT_SIZE + HISTORY_HEADER_PAD*2.0f;
    noneFieldBtn.rec = {MENU_DIV.x, MENU_DIV.y - headerHeight, MENU_DIV.width*0.1f, headerHeight}; 
    nameFieldBtn.rec = {noneFieldBtn.rec.x + noneFieldBtn.rec.width, MENU_DIV.y - headerHeight, MENU_DIV.width*0.7f, headerHeight};
    scoreFieldBtn.rec = {nameFieldBtn.rec.x + nameFieldBtn.rec.width, MENU_DIV.y - headerHeight, MENU_DIV.width*0.2f, headerHeight};
    
    nextPageBtn.rec = {MENU_DIV.x + MENU_DIV.width - RETURN_BTN_REC.width, RETURN_BTN_REC.y, RETURN_BTN_REC.width, RETURN_BTN_REC.height};
    prevPageBtn.rec = {nextPageBtn.rec.x - RETURN_BTN_REC.width - 10.0f, RETURN_BTN_REC.y, RETURN_BTN_REC.width, RETURN_BTN_REC.height};

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

    history.clear();

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

int ItemsInPage() {
    if(RECORDS_PER_PAGE*(curPage+1) >= history.size) {
        return RECORDS_PER_PAGE;
    }
    return min(RECORDS_PER_PAGE, history.size - (RECORDS_PER_PAGE*curPage));
}

void UpdateHistory() {
    if(curPage == 0) prevPageBtn.active = false;
    else prevPageBtn.active = true;

    if((curPage+1)*RECORDS_PER_PAGE >= history.size) nextPageBtn.active = false;
    else nextPageBtn.active = true;

    if(selectedField == NAME) {
        if(sortingAsc) nameFieldBtn.text = "Name ^";
        else nameFieldBtn.text = "Name v";
    } else {
        nameFieldBtn.text = "Name";
    }

    if(selectedField == SCORE) {
        if(sortingAsc) scoreFieldBtn.text = "Score ^";
        else scoreFieldBtn.text = "Score v";
    } else {
        scoreFieldBtn.text = "Score";
    }

    noneFieldBtn.update();
    nameFieldBtn.update();
    scoreFieldBtn.update();

    nextPageBtn.update();
    prevPageBtn.update();
}

void DrawHeader() {
    noneFieldBtn.draw();
    nameFieldBtn.draw();
    scoreFieldBtn.draw();
}

void DrawRecord(int i, Record& record, Vector2 pos) {
    float fontSize = RECORD_FONT_SIZE;
    const char* indexTxt = TextFormat("%d.", i);
    DrawText(indexTxt, pos.x, pos.y, fontSize, WHITE);
    DrawText(record.name.c_str(), pos.x + 90.0f, pos.y, fontSize, WHITE);
    const char* scoreTxt = TextFormat("%.2f", record.score);
    DrawText(scoreTxt, pos.x + MENU_DIV_W - MeasureText(scoreTxt, fontSize), pos.y, fontSize, WHITE);
}

void DrawHistory() {
    DrawHeader();
    int s = RECORDS_PER_PAGE*curPage;
    for(int i=0; i<ItemsInPage(); i++) {
        DrawRecord(s + i + 1, history[s + i], {MENU_DIV.x, MENU_DIV.y + HISTORY_HEADER_PAD*2 + i*30.0f});
    }
    nextPageBtn.draw();
    prevPageBtn.draw();
}

void SortRecordsByScore(bool asc) {
    Timer timer;
    timer_iniciar(&timer);

    auto _comp = [asc](Record& r1, Record& r2) {
        if(r1.score == r2.score) return asc ? r1.name < r2.name : r1.name > r2.name;
        return asc ? r1.score < r2.score : r1.score > r2.score;
    };

    auto _swap = [] (Record& r1, Record& r2) {
        swap(r1.name, r2.name);
        swap(r1.score, r2.score);
    };
    history.sort(_comp, _swap);

    cout << "History sorting time: " << timer_parar(&timer) << " seconds\n";
}

void SortRecordsByName(bool asc) {
    Timer timer;
    timer_iniciar(&timer);

    auto _comp = [asc](Record& r1, Record& r2) {
        if(r1.name == r2.name) return asc ? r1.score < r2.score : r1.score > r2.score;
        return asc ? r1.name < r2.name : r1.name > r2.name;
    };

    auto _swap = [] (Record& r1, Record& r2) {
        swap(r1.name, r2.name);
        swap(r1.score, r2.score);
    };
    history.sort(_comp, _swap);

    cout << "History sorting time: " << timer_parar(&timer) << " seconds\n";
}