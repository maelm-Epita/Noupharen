CC = g++
CFLAGS = -Wall -Wextra -fstack-protector -g -Wvla -O0
LFLAGS = -lm -lglfw -lGL -lX11 -lXrandr -lassimp
INCFLAGS = -I"include/" -g
SRCDIR = src
BUILDDIR = build
SRC = $(wildcard ${SRCDIR}/*.cpp)
OBJ = $(SRC:${SRCDIR}/%.cpp=${BUILDDIR}/%.o)
TARGET = main

.PHONY: all
all: ${TARGET}

${TARGET}: ${OBJ}
	${CC} $^ -o $@ ${LFLAGS} ${CFLAGS}

${BUILDDIR}/%.o: ${SRCDIR}/%.cpp
	${CC} -c $^ ${INCFLAGS} -o $@

.PHONY: clean
clean:
	rm -f ${TARGET} ${OBJ}
