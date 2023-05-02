cc = gcc
objs = temp/set.o guard/temp/guard.o
dirs = temp
CFLAGS = -O1

# Object files
temp/stack.o: set.h set.c guard/temp/guard.o
	$(CC) -c -g -o temp/set.o set.c

guard/temp/guard.o:
	$(MAKE) -C guard

# If there is a main.c file
test: temp/main.o $(objs)
	$(CC) -o a.out temp/main.o $(objs)

temp/main.o: main.c $(objs)
	$(CC) -c -g -o temp/main.o main.c

.PHONY: clean

clean:
	rm -rf temp ./*.o a.out
	rm -rf guard/temp

$(shell mkdir -p $(dirs))