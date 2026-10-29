#ifndef UTILS_H
#define UTILS_H

#include "constants.h"

Ingredient CharToItem(char c);
Ingredient GetUnpreparedItem(Ingredient item);
float GetCostumerDifficulty(std::string recipe, float patience);

#endif