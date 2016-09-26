BASE = Collision
OS := $(shell uname -s)
TARGET := ../lib$(BASE).a

CXX := g++
CXXFLAGS += -std=c++11 -Wall -g -O0 --coverage -Iinclude/
LDFLAGS += -static

SOURCES := $(shell find src/ -name "*.cpp")
OBJECTS := $(addprefix build/,$(SOURCES:.cpp=.o))
DEPENDS := $(OBJECTS:.o=.d)

OBJDIRS := $(sort $(dir $(OBJECTS)))

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET)
	find build/ -name "*.gcno" -exec rm {} \;
	find build/ -name "*.gcda" -exec rm {} \;
	find build/ -name "*.o" -exec rm {} \;
	find build/ -name "*.d" -exec rm {} \;

$(TARGET): $(OBJECTS)
	ar rvs -o $@ $(OBJECTS)

build/%.o build/%.d: %.cpp | $(OBJDIRS)
	$(CXX) $(CXXFLAGS) -c -o build/$*.o $<

$(OBJDIRS):
	mkdir -p $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif
