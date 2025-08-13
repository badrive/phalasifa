CC = cc 
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
SRC = main.c utiles.c parsing.c utiles2.c routine.c routine_utiles.c philo.c
NAME = philo
OBJ = $(SRC:.c=.o)
all : $(NAME)
$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME) 

re: fclean all