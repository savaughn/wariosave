# Makefile for building libwariosave.a
#
# Copyright (c) 2024 github/savaughn
#
# Distributed under the MIT License (MIT)
# (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)


# Compiler and flags
CC = gcc
CFLAGS = -c -Iinclude/

# Directories
SRCDIR = src
BUILDDIR = build
RELEASEDIR = $(BUILDDIR)/release

VERSION = 1.0.0

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BUILDDIR)/%.o)

# Library
LIBRARY = $(BUILDDIR)/libwariosave.a

# Rule to create the build directory
$(shell mkdir -p $(BUILDDIR))
$(shell mkdir -p $(RELEASEDIR))

# Rule to compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $< -o $@

# Rule to create the library
$(LIBRARY): $(OBJECTS)
	@ar rcs $(LIBRARY) $(OBJECTS)
	@rm -f $(OBJECTS) 
	@echo "Library created: $(LIBRARY)"

# Build the library
.PHONY: all
all: $(LIBRARY)

# Clean up
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(LIBRARY)

# Rule to copy library and include files to the release directory
.PHONY: release
release: $(LIBRARY)
	@cp $(LIBRARY) $(RELEASEDIR)/
	@cp -r include/ $(RELEASEDIR)/include/
	@echo "Release created: $(RELEASEDIR)/"
