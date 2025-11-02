TARGET = build/app
LIB_DIR = lib
SRC_DIR = src
BUILD_DIR = build
LIB_BUILD_DIR = $(BUILD_DIR)/lib

SRCS = $(wildcard $(SRC_DIR)/*.c)
LIB_SRCS = $(wildcard $(LIB_DIR)/src/*.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
LIB_OBJS = $(LIB_SRCS:$(LIB_DIR)/src/%.c=$(LIB_BUILD_DIR)/%.o)

LIBRARY = $(LIB_BUILD_DIR)/libproject.a

CC = gcc
CFLAGS = -I$(LIB_DIR)/include
LDFLAGS = -L$(LIB_BUILD_DIR) -lproject

$(TARGET): $(LIBRARY) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_BUILD_DIR)/%.o: $(LIB_DIR)/src/%.c | $(LIB_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBRARY): $(LIB_OBJS)
	ar rcs $@ $^

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIB_BUILD_DIR):
	mkdir -p $(LIB_BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: run clean