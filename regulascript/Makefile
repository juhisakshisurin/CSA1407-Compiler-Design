CC        = gcc
CFLAGS    = -Wall -Wextra -std=c11 -Iinclude
SRC       = $(wildcard src/*.c)
LIB_SRC   = $(filter-out src/main.c src/httpserver.c,$(SRC))
TARGET    = regula_server
TEST_BIN  = run_tests

ifeq ($(OS),Windows_NT)
    LDLIBS = -lws2_32
    TARGET := regula_server.exe
    TEST_BIN := run_tests.exe
    CFLAGS += -D__USE_MINGW_ANSI_STDIO=1
else
    LDLIBS = -lpthread
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDLIBS)

run: $(TARGET)
	./$(TARGET) 8080 www

test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(LIB_SRC) tests/test_compiler.c
	$(CC) $(CFLAGS) -o $(TEST_BIN) $(LIB_SRC) tests/test_compiler.c

clean:
	rm -f $(TARGET) $(TEST_BIN) *.o

.PHONY: all run test clean
