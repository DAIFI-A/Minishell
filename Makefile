SRCS = main.c parse.c path.c utils.c
SRCDIR = mand
OBJS_DIR = objs
CC = clang
CFLAGS =  -g -Wall -Wextra -Werror -fsanitize=address
NAME = mini
LIB = libft/libft.a
OBJS := $(SRCS:%.c=$(OBJS_DIR)/%.o)
INC = minishell.h

all: $(NAME)

$(OBJS_DIR):
	@mkdir $@

$(OBJS) : $(OBJS_DIR)/%.o: $(SRCDIR)/%.c $(INC) | $(OBJS_DIR)
	$(CC) -c -I $(shell brew --prefix readline)/include $< -o $@

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $^ -L $(shell brew --prefix readline)/lib -lreadline -o $(NAME) $(LIB)

$(LIB) :
	make bonus -C libft

clean:
	@rm -rf $(OBJS_DIR)
	make clean -C libft

fclean:	clean
	@rm -rf  $(NAME)
	make fclean -C libft

re: fclean all

-include $(DEPS)

.PHONY:	clean re fclean all