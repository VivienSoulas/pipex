NAME = pipex
SRC = pipex.c
OBJ = $(SRC:%.c=%.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -g

#indicates to look into the directories
PRINTF	= ./ft_printf
LIBFT	= ./libft

#indicates the library to use
PRINTF_LIB	= $(PRINTF)/ft_printf.a
LIBFT_LIB 	= $(LIBFT)/libft.a

#indicates where to look the header file 
HEADERS = -I $(PRINTF)

all: $(PRINTF_LIB) $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT)
	@echo "libft.a created"

$(PRINTF_LIB):
	@make -C $(PRINTF)
	@echo "fT_printf.a created"

$(NAME) : $(PRINTF_LIB) $(LIBFT_LIB) $(OBJ)
	@$(CC) $(OBJ) $(PRINTF_LIB) $(LIBFT_LIB) $(HEADERS) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

PHONY: all clean fclean re

clean:
	@rm -f $(OBJ)
	@make -C $(PRINTF) clean
	@make -C $(LIBFT) clean
	@echo "Objects files removed"

fclean: clean
	@rm -f $(NAME)
	@make -C $(PRINTF) fclean
	@make -C $(LIBFT) fclean
	@echo "executable removed"

re: fclean all