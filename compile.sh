g++ src/main.cpp src/cards.cpp src/costumer.cpp src/recipe.cpp src/utils.cpp src/avl.cpp src/history.cpp src/ui.cpp src/timer.cpp \
    -o game \
    -I./src \
    -I./raylib/examples/shapes \
    -lraylib -lm -lpthread -ldl -lrt -lX11