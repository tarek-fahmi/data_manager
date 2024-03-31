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
	make all
	chmod u+x tests.sh

run_tests: tests
	
	./tests.sh
	make clean

.PHONY:
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)