progname=Map
utest=utest_$(progname)
lib=lib$(progname).a
shared_lib=$(progname).so

CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11 -I. 
HEADER_DIR=headers
SRC_DIR=sources
TEST_DIR=tests
BUILDS=builds

debug:	 CXXFLAGS+=-g3
release: CXXFLAGS+=-g0 -DNDEBUG

ifeq ($(MAKECMDGOALS),)
	BUILD_DIR=$(BUILDS)/debug
else
	BUILD_DIR=$(BUILDS)/$(MAKECMDGOALS)
endif

SOURCES=main.cpp $(wildcard $(SRC_DIR)/*.cpp)
PREPROCS=$(patsubst %.cpp,$(BUILD_DIR)/%.ii,$(SOURCES))
ASSEMBLES=$(patsubst %.cpp,$(BUILD_DIR)/%.s,$(SOURCES))
OBJS=$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDS=$(patsubst %.cpp,$(BUILD_DIR)/%.d,$(SOURCES))

LIB_SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
LIB_PREPROCS=$(patsubst %.cpp,$(BUILD_DIR)/%.ii,$(LIB_SOURCES))
LIB_ASSEMBLES=$(patsubst %.cpp,$(BUILD_DIR)/%.s,$(LIB_SOURCES))
LIB_OBJS=$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(LIB_SOURCES))
LIB_DEPENDS=$(patsubst %.cpp,$(BUILD_DIR)/%.d,$(LIB_SOURCES))

UTEST_SOURCES=main_utest.cpp $(wildcard $(SRC_DIR)/*.cpp)
UTEST_PREPROCS=$(patsubst %.cpp,$(BUILD_DIR)/%.ii,$(UTEST_SOURCES))
UTEST_ASSEMBLES=$(patsubst %.cpp,$(BUILD_DIR)/%.s,$(UTEST_SOURCES))
UTEST_OBJS=$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(UTEST_SOURCES))
UTEST_DEPENDS=$(patsubst %.cpp,$(BUILD_DIR)/%.d,$(UTEST_SOURCES))

TEST_INPUTS=$(wildcard $(TEST_DIR)/*.input)
TESTS=$(patsubst $(TEST_DIR)/%.input,%,$(TEST_INPUTS))

debug:   $(BUILD_DIR) utest #$(shared_lib) $(lib) utest 
release: utest

qa: $(TESTS)

test%: $(progname)
	./$< < $(TEST_DIR)/$@.input > $(BUILD_DIR)/$(TEST_DIR)/$@.output 2>/dev/null || echo "Negative test"
	diff $(BUILD_DIR)/$(TEST_DIR)/$@.output $(TEST_DIR)/$@.expected   >/dev/null && echo "$@ PASSED" || echo "$@ FAILED"

utest: $(utest)
	./$<    

$(utest): $(UTEST_OBJS) | .gitignore
	$(CXX) $(CXXFLAGS) $^ -lgtest -o $@
	
$(progname): $(OBJS) | .gitignore
	$(CXX) $(CXXFLAGS) $^ -o $@
	
$(lib): $(LIB_OBJS) | .gitignore
	ar -crv $@ $^

$(shared_lib): $(LIB_OBJS) | .gitignore
	$(CXX) $(CXXFLAGS) $^ --shared -o $@

$(BUILD_DIR)/%.ii: %.cpp
	$(CXX) $(CXXFLAGS) -E $< -o $@
	$(CXX) $(CXXFLAGS) -MM $< -MT $@ > $(patsubst %.ii,%.d,$@) 

%.s: %.ii
	$(CXX) $(CXXFLAGS) -S $< -o $@

%.o: %.s
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@/$(TEST_DIR) $@/$(SRC_DIR)

.gitignore:
	echo $(progname)   >  .gitignore
	echo $(utest)      >> .gitignore
	echo $(BUILDS)     >> .gitignore
	echo $(lib)        >> .gitignore
	echo $(shared_lib) >> .gitignore

install:
	cp headers/$(progname).hpp /usr/local/include
	cp $(lib)                /usr/local/lib > /dev/null 2>&1 || echo "No static lib"
	cp $(shared_lib)         /usr/local/lib > /dev/null 2>&1 || echo "No dynamic lib"
	
clean:
	rm -rf $(BUILDS) $(progname) $(utest) $(lib) $(shared_lib) .gitignore

.PRECIOUS:  $(PREPROCS) $(ASSEMBLES) $(UTEST_PREPROCS) $(UTEST_ASSEMBLES)
.SECONDARY: $(PREPROCS) $(ASSEMBLES) $(UTEST_PREPROCS) $(UTEST_ASSEMBLES)

sinclude $(DEPENDS) $(UTEST_DEPENDS)
