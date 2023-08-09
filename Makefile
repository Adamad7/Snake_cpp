# all: compile link

# compile:
# 	g++ -c main.cpp -I"C:\Programowanie\SFML-2.6.0_64\include" -DSFML_STATIC

# link:
# 	g++ main.o -o main -L"C:\Programowanie\SFML-2.6.0_64\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

# clean:
# 	rm -f main *.o

# Compiler
CXX := g++       
# Compiler flags
CXXFLAGS :=   -I"..\SFML-2.6.0_64\include" -DSFML_STATIC -Iinclude 
# Linker flags
LDFLAGS :=    -L"..\SFML-2.6.0_64\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main     
# SFML_INCLUDE := -I".\SFML-2.6.0_64\include"
# SFML_LIB := -L".\SFML-2.6.0_64\lib"
SRCDIR := src
BUILDDIR := build

# tworzy listę źródeł z wszystkich plików w katalogu src o rozszerzeniu .cpp
SOURCES := $(wildcard $(SRCDIR)/*.cpp) 
# tworzy listę obiektów z wszystkich plików w katalogu build o rozszerzeniu .o
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES)) 
TARGET := $(BUILDDIR)/snake

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
#	@mkdir -p $(BUILDDIR)
#	@echo $(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^
#	$(CXX) $(SFML_INCLUDE) $(SFML_LIB) $(CXXFLAGS) $(LDFLAGS) -o $@ $^
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@ 

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
#	@mkdir -p $(BUILDDIR)
#	@echo $(CXX) $(CXXFLAGS) -c -o $@ $<
#	$(CXX) $(SFML_INCLUDE) $(SFML_LIB) $(CXXFLAGS) -c -o $@ $<
	$(CXX) $(CXXFLAGS) -c -o $@ $<





clean:
	rm build/*.o

TESTSRCDIR := tests
TESTOBJDIR := $(BUILDDIR)/tests
TESTBUILDDIR := $(BUILDDIR)

TESTSOURCES := $(wildcard $(TESTSRCDIR)/*.cpp)
TESTOBJECTS := $(patsubst $(TESTSRCDIR)/%.cpp,$(TESTOBJDIR)/%.o,$(TESTSOURCES))
TESTTARGET := $(TESTBUILDDIR)/testrunner

CXXFLAGS += -I$(TESTSRCDIR)   # Add Catch2 include path here (It's already in the repo)

.PHONY: test

test: $(TESTTARGET)
	$(TESTTARGET)

$(TESTTARGET): $(TESTOBJECTS) $(OBJECTS)
	@mkdir -p $(TESTBUILDDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(TESTOBJDIR)/%.o: $(TESTSRCDIR)/%.cpp
	@mkdir -p $(TESTOBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
