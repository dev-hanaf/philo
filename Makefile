RED = \033[0;31m
BOLD = \033[1m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
NAME = philo

GARBAGE = ./libs/gc
GNL = libs/get_next_line


INC = -Iheaders

SRC =  $(wildcard src/*.c)  $(wildcard src/*/*.c) 
OBJ = $(SRC:.c=.o)

all : header $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(INC) -o $(NAME) 

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
