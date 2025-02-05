NAME = 	pipex
SRC	 = 	pipex.c \
		utils.c\
		free.c
OBJ = $(SRC:%.c=%.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -g

#indicates to look into the directories
LIBFT	= ./libft
PRINTF	= ./ft_printf

#indicates the library to use
LIBFT_LIB 	= $(LIBFT)/libft.a
PRINTF_LIB	= $(PRINTF)/libftprintf.a

#indicates where to look the header file 
HEADERS = -I $(PRINTF)

all: $(PRINTF_LIB) $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT)
	@echo "libft.a created"

$(PRINTF_LIB):
	@make -C $(PRINTF)
	@echo "libftprintf.a created"

$(NAME) : $(LIBFT_LIB) $(PRINTF_LIB) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT_LIB) $(PRINTF_LIB) $(HEADERS) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

PHONY: all clean fclean re

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT) clean
	@make -C $(PRINTF) clean
	@echo "Objects files removed"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@make -C $(PRINTF) fclean
	@echo "executable removed"

re: fclean all