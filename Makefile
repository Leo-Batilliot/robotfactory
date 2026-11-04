##
## EPITECH PROJECT, 2024
## makefile
## File description:
## task 01
##

# FILES
SRC	=	src/lib/split_str.c 		\
		src/lib/my_strlen.c 		\
		src/lib/my_strncmp.c 		\
		src/lib/my_strcmp.c 		\
		src/lib/my_strncpy.c		\
		src/lib/my_strcat.c 		\
		src/lib/free_array.c 		\
		src/lib/linked_lists.c 		\
		src/lib/my_strdup.c 		\
		src/lib/array_to_str.c 		\
		src/lib/my_array_len.c 		\
		src/lib/total_array_len.c 	\
		src/lib/mini_printf.c 		\
		src/lib/my_strcpy.c 		\
		src/lib/my_get_nbr.c 		\
		src/main.c 					\
		src/loop_body.c 			\
		src/utils/op.c 				\
		src/main_loop.c				\
		src/utils/gest_args.c 		\
		src/lib/swap_end.c 			\
		src/utils/get_head_size.c 	\
		src/utils/get_label_err.c 	\

# COLORS
RED=\033[31m
GREEN=\033[32m
WHITE=\033[37m
BOLD=\033[1m
RESET=\033[0m

# VARIABLES
OBJ =	$(SRC:.c=.o)
FLAGS = -Wextra -Wall -W -Werror -I src/include -g
CC = gcc
NAME = asm

# PRINT COMPILATIONc
%.o: %.c
	@echo -e "$(GREEN)$(BOLD)[COMPILING]:\t$(RESET)$(GREEN)$<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

# PRINT AND THEN COMPILE
all: pre-compile $(NAME)

# PRINT INFO
pre-compile:
	@echo -e "$(WHITE)$(BOLD)\t$(WHITE)[COMPILATION...]$(RESET)"

# COMPILATION
$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAGS)
	@echo -e "$(WHITE)$(BOLD)\t[COMPILED SUCCESSFULLY]"
	@echo -e "[READY]:$(RESET)$(WHITE)\t$(NAME)$(RESET)"


# CLEAN OBJECT FILES
clean:
	@echo -e "$(WHITE)$(BOLD)\t[CLEANING OBJ...]$(RESET)"
	@for file in $(OBJ); do \
		if [ -f "$$file" ]; then \
			echo -e "$(RED)$(BOLD)[CLEAN]:\t$(RESET)$(RED)$$file$(RESET)"; \
			rm -f "$$file"; \
		fi; \
	done

# CLEAN EXEC / LIB
fclean:
	@echo -e "$(WHITE)$(BOLD)\t[CLEANING EXEC/LIB...]"
	@echo -e "$(RED)[CLEAN]:\t$(RESET)$(RED)$(NAME)$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) clean -s

# CLEAN EVERYTHING AND RE-COMPILE
re: fclean all
