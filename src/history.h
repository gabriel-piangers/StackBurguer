#ifndef HISTORY_H
#define HISTORY_H

#include "constants.h"

#define RECORDS_PER_PAGE 20

struct Record {
    std::string name;
    float score;
};

// Exports
void InitHistory(std::string path);
Record* GetRecords(int n = RECORDS_PER_PAGE, int page = 0);
int ItemsInPage(int n = RECORDS_PER_PAGE, int page = 0);
void SortRecordsByScore(bool asc = true);
void SortRecordsByName(bool asc = true);


#endif