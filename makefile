# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/ :)
TARGET_EXEC := mkpsin
BUILD_DIR := ./build
SRC_DIRS := ./mkpsin
SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := $(INC_FLAGS) -MMD -MP
UNAME_S := $(shell uname -s)
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
-include $(DEPS)
