/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:46:15 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/13 20:32:11 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../include/cub_3d.h"

# define WHITSPACE " \t\n\f\v\r"
# define MAPCHRS "NEWS10D"

typedef struct s_map t_map;
typedef struct s_game t_game;

typedef struct s_parse{
    
    int     fd;
    char    *line;
    char    **split;
    bool    details_part;
    bool    map_part;
    t_map   *map;
} t_parse;


/*****************checking_format.c********************/

bool	trim_line(t_parse *parser);
int	fetch_map_detail(t_parse *parser,t_game *game, char *file);
int	parsing_map(t_game *game, char *file);
int	check_map_file_format_add(char *file);
int	checking_map(int ac, char **av, t_game *game);





#endif
