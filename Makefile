CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -std=c99 -g
LDFLAGS := -static-libgcc -Wl,--gc-sections

SRC_DIR     := src
CMD_DIR     := command
BUILD_DIR   := build
BIN         := ush

SRC_FILES   := $(wildcard $(SRC_DIR)/*.c)
CMD_FILES   := $(wildcard $(CMD_DIR)/*.c)
ALL_SRCS    := $(SRC_FILES) $(CMD_FILES)

OBJ_FILES   := $(patsubst %.c, $(BUILD_DIR)/%.o, $(ALL_SRCS))


.PHONY: all
all: $(BIN)

$(BIN): $(OBJ_FILES)
	@echo " LD    $@"
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo " CC    $<"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo " CLEAN"
	rm -rf $(BUILD_DIR) $(BIN)

.PHONY: release
release: CFLAGS := -Wall -Wextra -Werror -O2 -std=c99
release: clean all
