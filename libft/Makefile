# Variable
SOURCES =   ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c

SOURCES_BONUS = ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

OBJECTS = $(SOURCES:.c=.o)

OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

# defautl if no arguments given with make 
all: $(NAME)

# link the library/create a static library
# ar creates the archive
# r adds the files to the library
# c creates the file if it doesn't exist
# s adds an index for faster readout of the library

# Bonus flag variable
BONUS_FLAG = 0

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)

# % is a rule, works for all .o and .c files
# -c = tells the compiler to compile the source file into an object file -o
# $< = first prerequisite (aka : the source file being compiled)
# $@ = target name (aka : object file)
[%.o: %.c]
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus

# clean object files
clean:
	@rm -f $(OBJECTS) $(OBJECTS_BONUS)

# clean all
fclean: clean
	@rm -f $(NAME)

# clean all and rebuild
re: fclean all

bonus: $(OBJECTS) $(OBJECTS_BONUS)
	@ar rcs $(NAME) $(OBJECTS) $(OBJECTS_BONUS)
