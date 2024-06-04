CC = lcc

MAIN_FILE = main.c
MAIN_RUNNER = GBInvader.c
SRCS_DIR = sprites
SRCS_COMPONENTS_DIR = components
INCLUDE_DIR = sprites
INCLUDE_COMPONENTS_DIR = components
BUILD_DIR = build

TARGET = GBInvader

SRCS = $(MAIN_FILE)
SRCS += $(MAIN_RUNNER)
SRCS += $(wildcard $(SRCS_DIR)/*.c)
SRCS += $(wildcard $(SRCS_COMPONENTS_DIR)/*/*.c)

OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

CFLAGS = -I$(INCLUDE_COMPONENTS_DIR) -I$(INCLUDE_DIR)

all: $(TARGET)
	
$(TARGET): $(OBJS)
	$(CC) -j4 $(LDFLAGS) -o $(BUILD_DIR)/$@.gb $^


$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)/$(dir $<)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

rebuild:
	$(MAKE) clean
	$(MAKE) all
	
.PHONY: all clean