g++ src/main.cpp src/cards.cpp src/costumer.cpp src/shop.cpp src/recipe.cpp src/utils.cpp src/avl.cpp src/history.cpp src/ui.cpp src/event_system.cpp src/metrics.cpp src/timer.cpp \
    -o game \
    -I./src/headers \
    -I./raylib/examples/shapes \
    -lraylib -lm -lpthread -ldl -lrt -lX11