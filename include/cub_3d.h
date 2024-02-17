/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:29:06 by nnavidd           #+#    #+#             */
/*   Updated: 2024/02/16 18:32:12 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB_3D_H
# define CUB_3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <sys/wait.h>
# include <limits.h>
# include <X11/X.h>
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/fts.h"
# include "../include/utils.h"
# include "../include/parser.h"

# define BLUE		"\033[38;5;4m"
# define GREEN		"\033[38;5;2m"  // For a bright green try 10 instead of 2
# define ORG		"\033[38;5;214m"
# define RED		"\033[38;5;196m"
# define RESET		"\033[0m"

# define SYSERR		0
# define NOSYSERR	1
# define ONLY_CHECK	2
# define WIDTH 256
# define HEIGHT 256


typedef struct s_parse t_parse;


# define MAX_WIDTH  1024
# define MAX_HEIGHT 1024

typedef struct s_map{
	int			resolution_x;
	int			resolution_y;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*sprite_texture;
	int			floor_color[3];
	char		**grid;
	int			ceiling_color[3];
	uint32_t	map_width;
	uint32_t	map_height;
	uint32_t	max_width;
	uint32_t	*widths;
}		t_map;

typedef struct s_pos{
	uint32_t	x;
	uint32_t	y;
}		t_pos;

typedef struct s_player{
	t_pos		pos;
}		t_player;


typedef struct s_game{
	t_map		*map;
	t_parse		*parser;
	t_player	ply;
}	t_game;

/////////////////////////////////////////////////////
////                     utils                  /////
/////////////////////////////////////////////////////



#endif