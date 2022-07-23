NAME= minishell

CC= gcc

CFLAGS= -Wall -Wextra -Werror

CFILES = mini.c

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

INC= mini.h

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OFILES)
	@$(CC) $(OFILES) -lreadline -L $(shell brew --prefix readline)/lib -o $(NAME)
	@echo "minishell ok"

$(OBJ_DIR):
	@mkdir obj

$(OFILES): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	@$(CC) -c $(CFLAGS) -I $(shell brew --prefix readline)/readline $< -o $@

clean :
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
