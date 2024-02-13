/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:28:33 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/13 14:25:33 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
// # include "../include/cub_3d.h"

typedef struct s_game t_game;
typedef struct s_parse t_parse;

/**************init_free_funcs.c***************/

void	initiate_map_variable(t_game *game);
void	initiate_parse_variable(t_parse *parser, t_game *game, char *file);
void	free_2d_str(char **map);
void	free_parser(t_parse *parser);
void	free_game(t_game *game);


/**************errors_handling.c***************/

char    *error_table(char *code);
int     error_handler(char *error, int no);

#endif
