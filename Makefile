NAME			:= cub3d

CC				:= gcc
CFLAGS			:= -Wextra -Wall -Werror 
CFLAGS			+= -Wunreachable-code -Ofast
# CFLAGS			:+ -fsanitize=address

DATA_INIT_SRCS	= ./main.c


LIBMLX			:= ./MLX42

HEADERS			:= -I ./include 
HEADERS			+= -I $(LIBMLX)/include

LIBS			:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

ALL_SRCS		:= $(DATA_INIT_SRCS)

OBJS			:= ${ALL_SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx