/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_fucns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:02:04 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/13 20:50:32 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	initiate_map_variable(t_game *game)
{
	game->map = (t_map *)ft_calloc(1, sizeof(t_map));
	game->map->resolution_x = 0;
	game->map->resolution_y = 0;
	game->map->no_texture = NULL;
	game->map->so_texture = NULL;
	game->map->ea_texture = NULL;
	game->map->we_texture = NULL;
	game->map->floor_color[0] = -1;
	game->map->ceiling_color[0] = -1;
	game->map->grid = NULL;
	game->map->map_width = 0;
	game->map->map_height = 120;
}

void	initiate_parse_variable(t_parse *parser, t_game *game, char *file)
{
	parser->fd = open(file, O_RDONLY);
	if (parser->fd == -1)
		error_handler("The cub file address is wrong.", SYSERR);
	parser->line = NULL;
	parser->split = NULL;
	parser->details_part = true;
	parser->map_part = false;
	parser->map = game->map;
}

void	free_2d_str(char **map)
{
	int		i;

	if (map == NULL)
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		map[i++] = NULL;
	}
	free(map);
	map = NULL;	
}

void	free_parser(t_parse *parser)
{
	if (parser != NULL)
	{
		if (parser->line)
			free(parser->line);
		if (parser->split != NULL)
			free_2d_str(parser->split);
		// free(parser->game);
		free(parser);
	}
}

void	free_game(t_game *game)
{
	if (game == NULL || game->map == NULL)
		return ;
	if (game->map->no_texture != NULL)
		free(game->map->no_texture);
	if (game->map->so_texture != NULL)
		free(game->map->so_texture);
	if (game->map->ea_texture != NULL)
		free(game->map->ea_texture);
	if (game->map->we_texture != NULL)
		free(game->map->we_texture);
	if (game->map->grid != NULL)
		free_2d_str(game->map->grid);
	if (game->map != NULL)
		free(game->map);
	free(game);
}
