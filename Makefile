CC=gcc
FLAGS=-Wall -Werror
OBJS=mtll.o main.o helpers.o
TARGET=mtll

build: all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

tests: $(TARGET)
	make all
	chmod u+x tests.sh

run_tests: tests
	./tests.sh
	make clean

.PHONY:
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)