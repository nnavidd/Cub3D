NAME		=	cub3D

# PROGRAMS #

CC			=	cc
RM			=	rm

# DIRECTORIES #

SRC_DIR		=	src
BUILD_DIR	=	build
SUB_DIRS	=	parsing

LIBFT_DIR	=	libs/libft
MLX_DIR		=	libs/MLX42
MLX_BUILD	=	$(MLX_DIR)/build

# FLAGS #

CFLAGS		=	-Wall -Wextra -Werror -MMD# -g3 -fsanitize=address
MLXFLAGS	=	-lglfw -framework Cocoa -framework OpenGL -framework IOKit
RMFLAGS		=	-rf
INCFLAGS	=	-I./include \
				-I./$(LIBFT_DIR)/include \
				-I./$(MLX_DIR) \
				-I./$(MLX_DIR)/include/MLX42

# FILES #

SRCS		=	$(SRC_DIR)/cub3d.c \
				$(foreach dir, $(SUB_DIRS), $(wildcard $(SRC_DIR)/$(dir)/*.c))
OBJS		=	$(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
DEPS		=	$(OBJS:.o=.d)

# ARCHIVES #

LIBFT		=	$(LIBFT_DIR)/libft.a
MLX42		=	$(MLX_BUILD)/libmlx42.a

# RULES #

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
	$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFT) $(MLX42) $(MLXFLAGS) -o $@ $(OBJS)

$(LIBFT):
	@echo "\033[38;5;214m-----Compiling the LIBFT files-----"
	@mkdir -p $(LIBFT_DIR)
	@git submodule update --init --recursive --remote $(LIBFT_DIR)
	@make -C $(LIBFT_DIR) --silent

$(MLX42):
	@echo "\033[38;5;214m-----Compiling the MLX files-----"
	@git submodule update --init --recursive --remote $(MLX_DIR)
	@brew install glfw
	@cmake -S $(MLX_DIR)/ -B $(MLX_BUILD) -DGLFW_FETCH=1
	@make -C $(MLX_BUILD) --silent

-include $(DEPS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(RMFLAGS) $(BUILD_DIR)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

libclean:
	$(RM) $(RMFLAGS) $(LIBFT_DIR) $(MLX_DIR)

allclean: libclean fclean

libupdate: libclean all

.PHONY: all clean fclean re libclean allclean libupdate
