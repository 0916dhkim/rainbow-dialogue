# Original : https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
TARGET_EXEC ?= rainbow-dialogue

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

MAIN_SRC := ./src/main.c  # source file with the main function
MAIN_OBJ := $(MAIN_SRC:%=$(BUILD_DIR)/%.o)

SRCS := $(shell find $(SRC_DIRS) \( -name *.cpp -or -name *.c -or -name *.s \) -not -name *.spec.* -not -path $(MAIN_SRC))
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

# Test files
TEST_SRCS := $(shell find $(SRC_DIRS) -name *.spec.cpp -or -name *.spec.c)
TEST_EXECS := $(TEST_SRCS:%=$(BUILD_DIR)/%.out)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS) $(MAIN_OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: test
test: $(TEST_EXECS)
	for test_exec in $(TEST_EXECS) ; do \
		$$test_exec ; \
	done

$(BUILD_DIR)/%.spec.cpp.out: %.spec.cpp.o $(OBJS)
	$(CC) $< -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.spec.c.out: $(BUILD_DIR)/%.spec.c.o $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
