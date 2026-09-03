CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
CPPFLAGS = -Iinclude

TARGET = minic

SOURCES = src/main.c src/lexer/lexer.c src/lexer/token.c

BUILD_DIR = build

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(SOURCES) include/lexer/lexer.h include/lexer/token.h
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $(TARGET)

tests: $(TARGET)
	@mkdir -p $(BUILD_DIR)
	@for input in tests/inputs/*.mc; do \
		name=$$(basename "$$input" .mc); \
		echo "Probando $$name..."; \
		./$(TARGET) "$$input" > "$(BUILD_DIR)/$$name.actual"; \
		diff -u "tests/expected/$$name.out" "$(BUILD_DIR)/$$name.actual" || exit 1; \
	done
	@echo "Todos los tests pasaron."

clean:
	$(RM) $(TARGET) $(TARGET).exe
	$(RM) -r $(BUILD_DIR)