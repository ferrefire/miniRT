CC = gcc
CFLAGS = -Iincludes/ -Iexternal/libft -Iexternal/minilibx
#LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
LDFLAGS = -Lexternal/libft -Lexternal/minilibx -lft -lm -lmlx -lX11 -lXi -lXext

SRC = $(wildcard sources/*.c)
#EXTSRC = src/glad.c
OBJDIR = obj/
#OBJ = $(addprefix $(OBJDIR), $(SRC:.cpp=.o)) $(addprefix $(OBJDIR), $(EXTSRC:.c=.o))
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))
#EXTOBJ = $(addprefix $(OBJDIR), $(EXTSRC:.c=.o))
DEPS = includes/*.h
MLX = external/minilibx/libmlx.a
LIBFT = external/minilibx/libft.a
NAME = miniRT

.PHONY: run clean fclean re

$(NAME): $(LIBFT) $(MLX) $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJDIR)%.o: %.c*
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

$(LIBFT):
	$(MAKE) all -C external/libft

$(MLX):
	$(MAKE) all -C external/minilibx

run: $(NAME)
	./$(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C external/libft

fclean: clean
	$(MAKE) clean -C external/minilibx
	$(MAKE) fclean -C external/libft
	rm -f $(NAME)

re: fclean $(NAME)