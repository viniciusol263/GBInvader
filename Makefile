CC = lcc

MAIN_FILE = main.c
SRCS_DIR = sprites
INCLUDE_DIR = sprites
BUILD_DIR = build

TARGET = HelloWorld

SRCS = $(wildcard $(SRCS_DIR)/*.c)
SRCS += $(MAIN_FILE)

OBJS = $(patsubst $(SRCS_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

CFLAGS = -I$(INCLUDE_DIR) 


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(BUILD_DIR)/$@.gb $^

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean