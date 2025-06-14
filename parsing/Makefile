NAME = minishell

# CFLAGS = -Wextra -Wall -Werror 

SRC = pars/parsing.c pars/parsing1.c pars/parsing2.c pars/tokenizer.c\
	  utils/ft_free.c utils/ft_split.c utils/ft_strdup.c utils/ft_strlen.c utils/ft_substr.c\
	  pars/envirement.c pars/redirection.c pars/expand.c pars/parsing3.c\
	  linked_list/lst_add_back.c linked_list/lst_new_add.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) ../inc/minishell.h
	$(CC) $(OBJ) -lreadline -fsanitize=address -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -rf $(OBJ)

fclean : clean   
	rm -rf $(NAME)

re : fclean all
