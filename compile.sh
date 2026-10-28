g++ src/main.cpp src/cards.cpp src/costumer.cpp src/recipe.cpp src/utils.cpp \
    -o game \
    -I./src \
    -lraylib -lm -lpthread -ldl -lrt -lX11