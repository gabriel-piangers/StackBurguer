#ifndef METRICS_H
#define METRICS_H

//Exports
void AddAvlNode();
void SetAvlHeight(int h);
void AddAvlRotation();
void AddAvlComp();
void AddAvlSearch();
void AddAvlSearchTime(float time);
void SetAvlLoadTime(float time);
void AddCacheHit();
void AddCacheMiss();
void SetCacheCollision(int colisions);
void SetCacheSize(int size);
void SetCacheCapacity(int capacity);
void SetHistoryEntries(int entries);
void SetHistorySortingTime(float time);

void SaveMetrics();

#endif