# Compiler
CXX := g++       
# Compiler flags
CXXFLAGS := -std=c++14  -I"..\SFML-2.6.0_64\include" -DSFML_STATIC -Iinclude -Icatch2
# Linker flags
LDFLAGS :=    -L"..\SFML-2.6.0_64\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main     
SRCDIR := src
BUILDDIR := build

SOURCES := $(wildcard $(SRCDIR)/*.cpp) 
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES)) 
TARGET := $(BUILDDIR)/snake

.PHONY: all clean test

all: $(TARGET)
	.\$(TARGET).exe

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@ 

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f build/*.o

TESTSRCDIR := tests
TESTOBJDIR := $(BUILDDIR)/tests
TESTBUILDDIR := $(BUILDDIR)

TESTSOURCES := $(wildcard $(TESTSRCDIR)/*.cpp)

TESTOBJECTS :=  $(patsubst $(TESTSRCDIR)/%.cpp,$(TESTOBJDIR)/%.o,$(TESTSOURCES))

TESTTARGET := $(TESTBUILDDIR)/testrunner

test: $(TESTTARGET)
	./$(TESTTARGET).exe

$(TESTTARGET): $(TESTOBJECTS) $(filter-out $(TESTBUILDDIR)/main.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@ 

$(TESTOBJDIR)/%.o: $(TESTSRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

catch.o: catch.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<