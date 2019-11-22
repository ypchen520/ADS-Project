CC = g++
EXEC = risingCity
OBJS = minHeap.o redBlackTree.o main.o util.o
SRCS := $(wildcard *.c)

BINS := $(SRCS:%.c=%)

all: ${EXEC}

#${EXEC}: %.o
${EXEC}: ${OBJS}
	${CC} ${OBJS} -o $@
%.o: %.cpp
	${CC} -c $<
.PHONY: clean

clean:
	rm -rvf *.o ${EXEC}