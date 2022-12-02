gcc main.c trees.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 &&
./main &&
rm main