BASE = Crash2D
OS := $(shell uname -s)
TARGET := ../$(BASE)_Demo

CXX := g++
CXXFLAGS := -std=c++11 -Wall -g -O0 -Iinclude/ -I../library/include/
LDFLAGS := -L../ 
LDLIBS := -lCollision -lsfml-graphics -lsfml-window -lsfml-system -lgcov

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
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

build/%.o build/%.d: %.cpp | $(OBJDIRS)
	$(CXX) $(CXXFLAGS) -c -o build/$*.o $<

$(OBJDIRS):
	mkdir -p $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif
