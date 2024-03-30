CC=gcc
FLAGS=-Wall -Werror
OBJS=mtll.o main.o
TARGET=mtll

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

<<<<<<< HEAD
%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@
=======
main:
	gcc -o mtll main.c mtll.c -g -fsanitize=address,leak
>>>>>>> e7594d1 (Error handling and memory leaks)

tests: $(TARGET)
	echo "Make my tests!"

run_tests: tests
	echo "Run my tests!"

.PHONY:
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)