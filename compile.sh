g++ src/main.cpp src/cards.cpp src/costumer.cpp src/recipe.cpp src/utils.cpp \
    -o game \
    -I./src \
    -I./raylib/examples/shapes \
    -lraylib -lm -lpthread -ldl -lrt -lX11