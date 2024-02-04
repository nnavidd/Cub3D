# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 15:53:18 by nnabaeei          #+#    #+#              #
#    Updated: 2023/05/14 17:38:02 by nnavidd          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(OBJ_DIR)/libft.a
BONUS_NAME = libft_bonus.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

cfiles = ft_isalpha.c ft_strlen.c ft_isdigit.c ft_memset.c \
         ft_isalnum.c ft_bzero.c ft_isascii.c ft_memcpy.c \
         ft_isprint.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
         ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
         ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
         ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
         ft_split.c ft_strjoin.c ft_strtrim.c ft_itoa.c \
         ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
         ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
         get_next_line.c get_next_line_utils.c ft_printf.c \
         check_flag.c check_type.c write_diu.c write_xp.c \
         write_sc.c ft_putnbr.c ft_putnbru.c ft_putnbrxp.c \
         ft_putstr.c ft_putchar.c

bonus = ft_lstadd_back.c ft_lstadd_front.c ft_lstdelone.c \
        ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstclear.c \
        ft_lstiter.c ft_lstmap.c 

OBJ_DIR = ../objs/libft
OBJ = $(addprefix $(OBJ_DIR)/,$(cfiles:.c=.o))
OBJ_B = $(addprefix $(OBJ_DIR)/,$(bonus:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ_B)
	ar rcs $(BONUS_NAME) $(OBJ_B)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all bonus