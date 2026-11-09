#ifndef HISTORY_H
#define HISTORY_H

#include "constants.h"

#define RECORDS_PER_PAGE 20
#define RECORD_FONT_SIZE 24.0f
#define HISTORY_HEADER_PAD 5

// Enums
enum HistoryField {
    NONE,
    NAME,
    SCORE,
};

struct Record {
    std::string name;
    float score;
};

// Exports
void InitHistory(std::string path);
void DrawHistory();
void UpdateHistory();
void SortRecordsByName(bool asc = true);
void SortRecordsByScore(bool asc = true);

#endif