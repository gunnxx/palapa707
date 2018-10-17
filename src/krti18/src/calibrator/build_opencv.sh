g++ $1 -o $2 `pkg-config --cflags --libs opencv4` -std=c++11 -lpthread
