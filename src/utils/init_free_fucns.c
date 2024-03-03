/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_fucns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:02:04 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/03/03 05:22:02 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	initiate_map(t_map *map)
{
	map->resolution_x = 0;
	map->resolution_y = 0;
	map->no_xpm = NULL;
	map->so_xpm = NULL;
	map->ea_xpm = NULL;
	map->we_xpm = NULL;
	map->floor_color[0] = -1;
	map->floor_color[1] = -1;
	map->floor_color[2] = -1;
	map->grid = NULL;
	map->ceiling_color[0] = -1;
	map->ceiling_color[1] = -1;
	map->ceiling_color[2] = -1;
	// map->map_width = 0;
	map->map_height = 0;
	map->widths = NULL;
}

void	initiate_parser(t_parse *parser, t_game *game, char *file)
{
	parser->fd = open(file, O_RDONLY);
	if (parser->fd == -1)
		error(game, "The cub file address is wrong.", SYSERR);
	parser->line = NULL;
	parser->split = NULL;
	// parser->details_part = true;
	parser->map_part = false;
	parser->map = &game->map;
	parser->game = game;
}

void	initiate_player(t_game *game)
{
	game->ply.pos.x = 0;
	game->ply.pos.y = 0;
	game->ply.plyr_x = game->ply.pos.x * TILE_SIZE + TILE_SIZE / 2; // player x position in pixels in the center of the tile
	game->ply.plyr_y = game->ply.pos.y * TILE_SIZE + TILE_SIZE / 2; // player y position in pixels in the center of the tile
	game->ply.fov_rd = (FOV * M_PI) / 180; // field of view in radians
	game->ply.angle = M_PI; // player angle
	//the rest of the variables are initialized to zero by calloc
}

void	initiate_hud(t_game *game)
{
	game->hud.map = NULL;
	game->hud.pos = (t_pos){0,0};
	game->hud.circle = NULL;
	game->hud.circle_bck = NULL;
	game->hud.img_ci_bck = NULL;
	game->hud.ply = NULL;
	game->hud.img_ply = NULL;
	game->hud.w_dot = NULL;
	game->hud.b_dot = NULL;
	game->hud.img_wall = NULL;
}

void	initiate_game(t_game *game, char *file)
{
	// game->parser = (t_parse *)ft_calloc(1, sizeof(t_parse));
	// game->map = (t_map *)ft_calloc(1, sizeof(t_map));
	initiate_map(&game->map);
	initiate_parser(&game->parser, game, file);
	initiate_player(game);
	initiate_hud(game);
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

// void	free_parser(t_parse *parser)
// {
// 	if (parser != NULL)
// 	{
// 		if (parser->line)
// 			free(parser->line);
// 		if (parser->split != NULL)
// 			free_array(parser->split);
// 		// free(parser->game);
// 		free(parser);
// 	}
// }
void	free_map(t_map *map)
{
	
	if (map->no_xpm && map->no_xpm != NULL)
		free(map->no_xpm);
	if (map->so_xpm != NULL)
		free(map->so_xpm);
	if (map->ea_xpm != NULL)
		free(map->ea_xpm);
	if (map->we_xpm != NULL)
		free(map->we_xpm);
	if (map->grid != NULL)
		free_array(map->grid);
	if (map->widths)
		free(map->widths);
	// free(map);
	// map = NULL;
}

void	free_hud(t_game *game)
{
	mlx_delete_image(game->mlx, game->hud.circle); // delete the image
	mlx_delete_image(game->mlx, game->hud.circle_bck); // delete the image
	mlx_delete_image(game->mlx, game->hud.img_ci_bck); // delete the image
	mlx_delete_image(game->mlx, game->hud.img_ply); // delete the image
	mlx_delete_image(game->mlx, game->hud.img_wall); // delete the image
	mlx_delete_texture(game->hud.w_dot);
	mlx_delete_texture(game->hud.b_dot);
	mlx_delete_texture(game->hud.ply);
	if (game->hud.map)
		free_array(game->hud.map);
}

void	free_mlx(t_game *game)
{
	mlx_delete_image(game->mlx, game->scn.img);
	mlx_close_window(game->mlx); // close the window
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void 	free_raycast(t_ray *ray)
{
	(void)ray;
}

void	close_game(t_game *game)
{
	free_map(&game->map);
	free_hud(game);
	free_raycast(&game->ray);
	free_mlx(game);
	// if (game->parser != NULL)
		// free(game->parser);
	// game->parser = NULL;
	// free(game);
	game = NULL;
}
