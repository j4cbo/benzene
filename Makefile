# Directories
SRC_DIR = src
BIN_DIR = bin
GTEST_DIR = googletest

# benzene source files
SRCS = \
    demo.cpp \
    device.cpp \
    device_registry.cpp \
    ilda_output_device.cpp \
    q8_24_unittest.cpp \
    segment.cpp \
    segment_builders.cpp \
    segment_unittest.cpp \

# Flags
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++1y

TEST_PROGRAM = benzene_test

# Base build rule
all: $(TEST_PROGRAM)

.PHONY: clean
clean :
	rm -rf $(TEST_PROGRAM) $(BIN_DIR)

# Gtest stuff.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
$(BIN_DIR)/gtest-all.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o $@
$(BIN_DIR)/gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o $@
$(BIN_DIR)/gtest_main.a: $(BIN_DIR)/gtest-all.o $(BIN_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

OBJS = $(addprefix $(BIN_DIR)/,$(SRCS:.cpp=.o))
DEPS = $(addprefix $(BIN_DIR)/,$(SRCS:.cpp=.d))

-include $(DEPS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(GTEST_HEADERS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -c $< -o $@

$(TEST_PROGRAM): $(OBJS) $(BIN_DIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $^ -o $@
	./$(TEST_PROGRAM)
