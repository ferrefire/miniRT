CC = gcc
CFLAGS = -Iincludes/ -Iexternal/minilibx
#LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
LDFLAGS = -Lexternal/minilibx -lm -lmlx -lX11 -lXi -lXext

SRC = $(wildcard sources/*.c)
#EXTSRC = src/glad.c
OBJDIR = obj/
#OBJ = $(addprefix $(OBJDIR), $(SRC:.cpp=.o)) $(addprefix $(OBJDIR), $(EXTSRC:.c=.o))
OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))
#EXTOBJ = $(addprefix $(OBJDIR), $(EXTSRC:.c=.o))
DEPS = includes/*.h
MLX = external/minilibx/libmlx.a
NAME = miniRT

.PHONY: run clean fclean re

$(NAME): $(MLX) $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJDIR)%.o: %.c*
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@

$(MLX):
	$(MAKE) all -C external/minilibx

run: $(NAME)
	./$(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) clean -C external/minilibx
	rm -f $(NAME)

re: fclean $(NAME)