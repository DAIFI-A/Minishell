NAME= minishell

CC= gcc

CFLAGS= -Wall -Wextra -Werror

CFILES = mini.c ft_header.c ft_lexer.c ft_lst_lexer.c ft_lst_env.c ft_parser.c ft_environment.c ft_expand.c

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

LIBFT = libft/libft.a

G_N_T =

INC= mini.h

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OFILES) $(LIBFT)
	@$(CC) $(OFILES) $(LIBFT) -L $(shell brew --prefix readline)/lib -lreadline -o $(NAME)
	@echo "minishell ok"

$(OBJ_DIR):
	@mkdir obj

$(OFILES): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	@$(CC) -c $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(LIBFT):
	make -C libft

clean :
	@rm -rf $(OBJ_DIR)
	@make clean -C libft
fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all
