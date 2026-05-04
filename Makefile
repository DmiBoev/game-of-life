CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lncurses
SRC = game_of_life.c
HEADER = game_of_life.h
BUILD_DIR = build
PATTERNS_DIR = pattern

TARGETS = edem gasper Generate HWSS LongShip spaseShip

.PHONY: all clean rebuild $(TARGETS)
all: $(TARGETS)

# Универсальное правило для сборки всех целей
$(TARGETS):
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(BUILD_DIR)/$@ $(LDFLAGS)

run_%: %
	./$(BUILD_DIR)/$* < $(PATTERNS_DIR)/$*.txt

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all
