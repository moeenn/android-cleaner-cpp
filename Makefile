PROJECT = android-cleaner

CC = clang++
SRC_DIR=./src
SRC = $(wildcard ${SRC_DIR}/*.cpp)
OBJ = ${SRC:.cpp=.o}
LIBS = -lm
CFLAGS = -Wextra -Werror -Wall -std=c++17 -Wc++17-extensions
BINARY = bin/${PROJECT}

main: ${OBJ}
	${CC} -o ${BINARY} ${SRC_DIR}/*.o ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} $<

clean:
	@echo "cleaning executables..."
	@rm ${SRC_DIR}/*.o
	@rm ${BINARY}
