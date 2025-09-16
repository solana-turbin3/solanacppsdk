# Simple Makefile for Solana C++ SDK

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -Llib -lsodium

# Source files
SOURCES = src/solana/base58.cpp src/solana/publicKey.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Test files
TEST_SOURCES = tests/solana/test_base58.cpp tests/solana/test_publicKey.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_TARGETS = $(TEST_SOURCES:.cpp=.exe)

# Main target
libsolanacppsdk.a: $(OBJECTS)
	ar rcs $@ $^

# Test targets
%.exe: %.o libsolanacppsdk.a
	$(CXX) -o $@ $< libsolanacppsdk.a $(LDFLAGS)

# Object file compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Build all tests
tests: libsolanacppsdk.a $(TEST_TARGETS)

# Clean
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TEST_TARGETS) libsolanacppsdk.a

.PHONY: tests clean