CC = emcc
CXX = emcc
LD = emcc
LDFLAGS = -Os -s EXPORTED_FUNCTIONS="['_main2', '_main']" -s NO_EXIT_RUNTIME=1
SIZE = size
