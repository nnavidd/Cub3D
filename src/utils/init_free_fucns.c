/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_fucns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:02:04 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/15 23:56:06 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	initiate_map(t_map *map)
{
	map->resolution_x = 0;
	map->resolution_y = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->ea_texture = NULL;
	map->we_texture = NULL;
	map->floor_color[0] = -1;
	map->floor_color[1] = -1;
	map->floor_color[2] = -1;
	map->grid = NULL;
	map->ceiling_color[0] = -1;
	map->ceiling_color[1] = -1;
	map->ceiling_color[2] = -1;
	map->map_width = 0;
	map->map_height = 0;
	map->widths = NULL;
}

void	initiate_parser(t_parse *parser, t_game *game, char *file)
{
	parser->fd = open(file, O_RDONLY);
	if (parser->fd == -1)
		error_handler("The cub file address is wrong.", SYSERR);
	parser->line = NULL;
	parser->split = NULL;
	// parser->details_part = true;
	// parser->map_part = false;
	parser->map = game->map;
}

void	free_array(char **map)
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
			free_array(parser->split);
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
		free_array(game->map->grid);
	if (game->map->widths)
		free(game->map->widths);
	if (game->map != NULL)
		free(game->map);
	if (game->parser != NULL)
		free(game->parser);
	free(game);
}
