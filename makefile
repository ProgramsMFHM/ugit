CC=gcc
EXEC=ugit
GRUPO=G1
NTAR=2

SRC_DIR=src
OBJ_DIR=obj
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
INCLUDE=-I./incs/
LIBS=
#LIBS= -lm

CFLAGS=-Wall -Wextra -Wpedantic -O3
LDFLAGS= -Wall -lm

all: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o build/$(EXEC) $(OBJ_FILES) $(INCLUDE) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDE)

.PHONY: clean folders
clean:
	rm -f $(OBJ_FILES)
	rm -f build/$(EXEC)

folders:
	mkdir -p src obj incs build docs

run:
	@./build/${EXEC}

doc:
	doxygen