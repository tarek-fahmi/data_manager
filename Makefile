CC=gcc
FLAGS=-Wall -Werror
TARGET=mtll

all: $(TARGET)

$(TARGET): $(TARGET).c
    $(CC) $(FLAGS) $^ -o $@

tests: $(TARGET)
    echo "Make my tests!"

run_tests: tests
    echo "Run my tests!"
