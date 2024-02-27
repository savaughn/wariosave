# Makefile for building example
#
# Copyright (c) 2024 github/savaughn
#
# Distributed under the MIT License (MIT)
# (See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)

APP_NAME = wario-save
SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard include/*.h)
DEPDIR = deps
BUILDDIR = build

# Compiler and linker flags
CC = gcc
INCLUDES = -Iinclude/ -I../lib/include/

# Generate object files and dependency files
OBJECTS = $(SOURCES:src/%.c=$(BUILDDIR)/%.o)
DEPS = $(patsubst %.c,$(DEPDIR)/%.d,$(SOURCES))

CFLAGS = -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-value -Wno-unused-result -Wno-unused-label -Wno-unused-local-typedefs
LDFLAGS = -L../lib/build -lwariosave

# Include dependency files
-include $(DEPS)

all: $(APP_NAME)
	@rm -f $(OBJECTS)

$(APP_NAME): $(OBJECTS) | $(DEPDIR)
	@$(CC) $(OBJECTS) -o $(BUILDDIR)/$(APP_NAME) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

$(BUILDDIR)/%.o: src/%.c | $(DEPDIR)
	@$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@$(CC) -MM $< $(INCLUDES) | sed 's,^,$(DEPDIR)/,' > $(@:.o=.d)

clean:
	@rm -f $(OBJECTS) $(BUILDDIR)/$(APP_NAME)
	@rm -rf $(DEPDIR)

launch: $(APP_NAME)
	@./$(BUILDDIR)/$(APP_NAME) "saves/wario.sav"
	@rm -f $(OBJECTS)

$(DEPDIR):
	@mkdir -p $(DEPDIR)

.PHONY: all clean launch
