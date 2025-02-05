NAME = 	pipex
SRC	 = 	pipex.c \
		utils.c\
		free.c
OBJ = $(SRC:%.c=%.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -g

#indicates to look into the directories
LIBFT	= ./libft

#indicates the library to use
LIBFT_LIB 	= $(LIBFT)/libft.a

#indicates where to look the header file 
HEADERS = -I $(LIBFT)

all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT)
	@echo "libft.a created"

$(NAME) : $(LIBFT_LIB) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT_LIB) $(HEADERS) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

PHONY: all clean fclean re

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT) clean
	@echo "Objects files removed"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@echo "executable removed"

re: fclean all