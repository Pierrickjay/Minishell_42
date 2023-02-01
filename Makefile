COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

CC=gcc
CFLAGS= -MMD -g3 -Wall -Werror -Wextra
INCLUDE= ./srcs/libft/libft.a
#HEADERS = philosophers.h
SRC= main.c
OBJ=$(SRC:%.c=build/%.o)
NAME=minishell
NAMEBONUS=

all : $(NAME)

.PHONY: all

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(INCLUDE) -o $(NAME)
	@echo "$(COLOUR_GREEN)		*------------------------*"
	@echo "$(COLOUR_GREEN)		|    Creating the file   |"
	@echo "$(COLOUR_GREEN)		*------------------------*"

bonus : $(NAMEBONUS)

.PHONY: bonus

build/%.o : %.c
	@echo "$(COLOUR_BLUE)		*------------------------*"
	@echo "$(COLOUR_BLUE)		|       ar rc libft      |"
	@echo "$(COLOUR_BLUE)		*------------------------*"
	@make --no-print-directory -C ./srcs/libft
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(COLOUR_BLUE)		*------------------------*"
	@echo "$(COLOUR_BLUE)		|    Creating the .o     |"
	@echo "$(COLOUR_BLUE)		*------------------------*"

clean:
	@echo "$(COLOUR_RED)		*------------------------*"
	@echo "$(COLOUR_RED)		|    Cleaning build      |"
	@echo "$(COLOUR_RED)		*------------------------*"
	@rm -rf build
	@rm -rf build_bonus
	@rm -rf libft/build

.PHONY: clean

fclean : clean
	@echo "$(COLOUR_RED)		*------------------------*"
	@echo "$(COLOUR_RED)		|  Cleaning all the exec |"
	@echo "$(COLOUR_RED)		*------------------------*"
	@rm -f $(NAME)
	@rm -f $(NAMEBONUS)

.PHONY: fclean

re : fclean all

.PHONY: re
