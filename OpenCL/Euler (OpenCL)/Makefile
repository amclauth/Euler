# Directories
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = build

# All sources
BASE_SOURCES := $(shell find $(SRC_DIR)/base -name '*.cpp')
PROB_SOURCES := $(shell find $(SRC_DIR)/problems -name '*.cpp')
UTIL_SOURCES := $(shell find $(SRC_DIR)/util -name '*.cpp')
TEST_SOURCES := $(shell find $(SRC_DIR)/test -name '*.cpp')

SRC_DIR_LISTING := $(shell echo $(BASE_SOURCES) $(PROB_SOURCES) $(UTIL_SOURCES) $(TEST_SOURCES) | xargs dirname | uniq | sed 's/$(SRC_DIR)\///g')

# All objects
BASE_O = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(BASE_SOURCES))
PROB_O = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(PROB_SOURCES))
UTIL_O = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(UTIL_SOURCES))
TEST_O = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SOURCES))

# Flags
CFLAGS = -O2 -Wall -g
LDFlags= -L
LDADD= -lrt -lOpenCL -lm

# Compile
CXX=g++

all:	full \
		single \
		test \
		discovery
		
# All problem headers
#problem_headers.h: 
#	for i in `find src/problems -name "*.cpp"`; do echo "#include \"$$i\"" >> problem_headers.h; done;

# Full program (runs all problems)
full:	buildrepo $(BIN_DIR)/full

$(BIN_DIR)/full:	$(BASE_O) $(PROB_O) $(UTIL_O) $(SRC_DIR)/full.cpp
	$(CXX) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(LDADD)
	
# Single program (runs a single instance for testing)
single:	buildrepo $(BIN_DIR)/single

$(BIN_DIR)/single:	$(BASE_O) $(PROB_O) $(UTIL_O) $(SRC_DIR)/single.cpp
	$(CXX) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(LDADD)
	
# Test suite
test:	buildrepo $(BIN_DIR)/test
$(BIN_DIR)/test:     $(BASE_O) $(PROB_O) $(UTIL_O) $(TEST_O)
	$(CXX) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(LDADD)

# Discovery suite
discovery: $(BIN_DIR)/discovery
$(BIN_DIR)/discovery: $(BASE_SOURCES) $(SRC_DIR)/discovery.cpp
	$(CXX) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(LDADD)

### Output helpers
$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cpp
	$(CXX) -c $(LDFLAGS) $(CFLAGS) -o $@ $< $(LDADD)
	
buildrepo:
	@$(call make-repo)

define make-repo
	mkdir -p $(OBJ_DIR)
	for dir in $(SRC_DIR_LISTING); \
	do \
		mkdir -p $(OBJ_DIR)/$$dir; \
	done
endef
	
# Clean
clean: 
	rm -r $(BIN_DIR)/* $(OBJ_DIR)/*
