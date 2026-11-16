#include "metrics.h"
#include <fstream>

using namespace std;

// Tracked metrics
int avlNodes = 0;
int avlHeight = 0;
int avlRotations = 0;
int avlComp = 0; // Recursive Search calls
int avlSearches = 0;
float avlSearchTime = 0.0f;
float avlLoadTime = 0.0f;
int cacheHits = 0;
int cacheMisses = 0;
int cacheColissions = 0;
int cacheSize = 0;
int cacheCapacity = 0;
int historyEntries = 0;
float historySortingTime = 0.0f;

void AddAvlNode() {
    avlNodes++;
}

void SetAvlHeight(int h) {
    avlHeight = h;
}

void AddAvlRotation() {
    avlRotations++;
}

void AddAvlComp() {
    avlComp++;
}

void AddAvlSearch() {
    avlSearches++;
}

void AddAvlSearchTime(float time) {
    avlSearchTime += time;
}

void SetAvlLoadTime(float time) {
    avlLoadTime = time;
}

void AddCacheHit() {
    cacheHits++;
}

void AddCacheMiss() {
    cacheMisses++;
}

void SetCacheCollision(int colisions) {
    cacheColissions = colisions;
}

void SetCacheSize(int size) {
    cacheSize = size;
}

void SetCacheCapacity(int capacity) {
    cacheCapacity = capacity;
}

void SetHistoryEntries(int entries) {
    historyEntries = entries;
}

void SetHistorySortingTime(float time) {
    historySortingTime = time;
}

void SaveMetrics() {
    ofstream file("data/metrics.log");
    file << "=== RELATORIO DE DESEMPENHO ===\n\n";

    file << "-- AVL: carregamento --\n";
    file << "Nos inseridos: " << avlNodes << "\n";
    file << "Altura resultante: " << avlHeight << "\n";
    file << "Rotacoes (insercao): " << avlRotations << "\n";
    file << "Tempo de carregamento: " << avlLoadTime << " s\n";
    file << "\n-- Historico: carregamento --\n";
    file << "Entradas carregadas: " << historyEntries << "\n";
    file << "\n-- AVL: buscas durante a partida --\n";
    file << "Total de buscas: " << avlSearches << "\n";
    file << "Total de comparacoes: " << avlComp << "\n";
    file << "Media de comparacoes por busca: " << (float) avlComp / (float) avlSearches << "\n";
    file << "Tempo total acumulado: " << avlSearchTime << " s\n";
    file << "\n-- Tabela hash --\n";
    file << "Tamanho (m): " << cacheCapacity << "\n";
    file << "Entradas ocupadas (n): " << cacheSize << "\n";
    file << "Fator de carga (lambda): " << (float) cacheSize / (float) cacheCapacity << "\n";
    file << "Total de hits: " << cacheHits << "\n";
    file << "Total de misses: " << cacheMisses << "\n";
    file << "Taxa de acerto: " << (float) cacheHits / (float) (cacheHits + cacheMisses) << "\n";
    file << "Total de colisoes: " << cacheColissions << "\n";
    file << "\n-- Ordenacao do historico (ao acessar Historico) --\n";
    file << "Tamanho: " << historyEntries << " entradas\n";
    file << "Quick Sort: " << historySortingTime << " s\n";
    file << "\n================================\n";
}

