RED = \033[0;31m
BOLD = \033[1m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
NAME = philo


INC = -Iheaders

SRC =  src/main.c src/parser/check_arguments.c src/parser/data_init.c src/routine/initializer.c src/routine/monitor.c src/routine/routine.c src/routine/write_status.c src/utils/ft_putstr.c src/utils/ft_sleep.c

OBJ = $(SRC:.c=.o)

all : header $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME) 

%.o:%.c
	$(CC) $(CFLAGS) $(INC)  -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY : $(OBJ)

header:
	@echo "$(GREEN)"
	@echo "░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓██████▓▒░ " 
	@echo "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░" 
	@echo "░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░" 
	@echo "░▒▓███████▓▒░░▒▓████████▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░" 
	@echo "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░" 
	@echo "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░" 
	@echo "░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓████████▓▒░▒▓██████▓▒░ " 
	@echo "$(NC)"  
	@echo "$(GREEN)################## PHILO MANDATORY #####################$(NC)\n"
