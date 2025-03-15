##
## EPITECH PROJECT, 2025
## nn/objdump
## File description:
## Makefile
##

CC      = gcc
CFLAGS  = -I./include -std=gnu17 \
          -Wall -Wextra -Werror -pedantic -Wconversion -g3 \
		  -O3
TEST_FLAGS = -lcriterion --coverage

LDFLAGS =

SRC_DIR   = src
OBJ_DIR   = objects
TEST_DIR  = tests

PROGRAMS  = nm objdump

SHARED_SRC = $(wildcard $(SRC_DIR)/shared/*.c)
NM_SRC     = $(wildcard $(SRC_DIR)/nm/*.c)
OBJDUMP_SRC = $(wildcard $(SRC_DIR)/objdump/*.c)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)

SHARED_OBJ = $(patsubst $(SRC_DIR)/shared/%.c, $(OBJ_DIR)/shared/%.o, \
					$(SHARED_SRC))
NM_OBJ     = $(patsubst $(SRC_DIR)/nm/%.c, $(OBJ_DIR)/nm/%.o, \
                    $(NM_SRC))
OBJDUMP_OBJ = $(patsubst $(SRC_DIR)/objdump/%.c, $(OBJ_DIR)/objdump/%.o, \
                    $(OBJDUMP_SRC))

TEST_OBJ = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/tests/%.o, \
                    $(TEST_SRC))

NM_OBJ_NO_MAIN := $(filter-out $(OBJ_DIR)/nm/main.o, $(NM_OBJ))
OBJDUMP_OBJ_NO_MAIN := $(filter-out $(OBJ_DIR)/objdump/main.o, $(OBJDUMP_OBJ))


NM_BIN		= my_nm
OBJDUMP_BIN = my_objdump
TEST_BIN = unit_tests
GCOVR = gcovr

GREEN      = \033[1;32m
RED        = \033[1;31m
ILC 	   = \033[3m
ORANGE     = \033[38;5;214m
RST      = \033[0m

all: $(PROGRAMS)

nm: $(SHARED_OBJ) $(NM_OBJ)
	@$(CC) $(CFLAGS) -o $(NM_BIN) $^ $(LDFLAGS)
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(NM_BIN)$(RST)\n\n"

objdump: $(SHARED_OBJ) $(OBJDUMP_OBJ)
	@$(CC) $(CFLAGS) -o $(OBJDUMP_BIN) $^ $(LDFLAGS)
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(OBJDUMP_BIN)$(RST)\n\n"

tests_run: $(TEST_OBJ) $(NM_OBJ_NO_MAIN) $(OBJDUMP_OBJ_NO_MAIN) $(SHARED_OBJ)
	@$(CC) -o $(TEST_BIN) $(TEST_OBJ) $(NM_OBJ_NO_MAIN) \
		$(OBJDUMP_OBJ_NO_MAIN) $(SHARED_OBJ) $(TEST_FLAGS)
	@./$(TEST_BIN)
	@$(GCOVR)

$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) --coverage -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING TEST: $(RST) $(ILC)$<$(RST)\n"

$(OBJ_DIR)/shared/%.o: $(SRC_DIR)/shared/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING: $(RST) $(ILC)$<$(RST)\n"

$(OBJ_DIR)/nm/%.o: $(SRC_DIR)/nm/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING: $(RST) $(ILC)$<$(RST)\n"

$(OBJ_DIR)/objdump/%.o: $(SRC_DIR)/objdump/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING: $(RST) $(ILC)$<$(RST)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)[❌] CLEAN:    $(RST) Removed $(ILC)$(OBJ_DIR)$(RST)\n\n"

fclean: clean
	@rm -f $(NM_BIN) $(OBJDUMP_BIN) $(TEST_BIN)
	@printf "$(RED)[❌] FCLEAN:   $(RST) Removed $(ILC)executables$(RST)\n\n"

re: fclean all

.PHONY: all nm objdump clean fclean re tests_run
