CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -g
LDFLAGS  := -static-libgcc -Wl,--gc-sections

SRC_DIR     := src
CMD_DIR     := command
BUILD_DIR   := build
BIN_DIR     := bin
INCLUDE_DIR := include
LIB_DIR     := lib

BIN         := $(BIN_DIR)/ush
LIB         := $(LIB_DIR)/libush.a

SRC_FILES       := $(wildcard $(SRC_DIR)/*.c)
SRC_CMD_FILES   := $(wildcard $(SRC_DIR)/commands/*.c)
CMD_FILES       := $(wildcard $(CMD_DIR)/*.c)

ALL_SRCS        := $(SRC_FILES) $(SRC_CMD_FILES) $(CMD_FILES)
LIB_SRCS        := $(SRC_FILES) $(SRC_CMD_FILES)

OBJ_FILES       := $(patsubst %.c, $(BUILD_DIR)/%.o, $(ALL_SRCS))
LIB_OBJ_FILES   := $(patsubst %.c, $(BUILD_DIR)/%.o, $(LIB_SRCS))

CFLAGS += -I$(INCLUDE_DIR)

.PHONY: all lib clean release

## ---------------------------------------
all: $(BIN)

$(BIN): $(OBJ_FILES)
	echo " LD    $@"
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@

## ---------------------------------------
lib: $(LIB)

$(LIB): $(LIB_OBJ_FILES)
	echo " AR    $@"
	mkdir -p $(LIB_DIR)
	ar rcs $@ $^

## ---------------------------------------
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	echo " CC    $<"
	$(CC) $(CFLAGS) -c $< -o $@

## ---------------------------------------
clean:
	echo " CLEAN"
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(LIB_DIR)

## ---------------------------------------
release: CFLAGS := -Wall -Wextra -Werror -O2 -std=c99
release: clean all
