# Copyright (c) 2025 github/savaughn
# Distributed under the MIT License (MIT)
# See accompanying file LICENSE.txt or copy at http://opensource.org/licenses/MIT)

CC = gcc
CFLAGS = -Wall -I../lib/include -I/opt/homebrew/Cellar/cunit/2.1-3/include
LDFLAGS = -L/opt/homebrew/Cellar/cunit/2.1-3/lib -L../lib/build -lcunit -lwariosave
TARGET = wariosave_test
SRC = $(wildcard src/*.c)

all: $(TARGET)

$(TARGET): $(SRC)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TARGET)
	@./$(TARGET)

clean:
	@rm -f $(TARGET)