/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:16:02 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/15 21:03:50 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void print_map_details(t_game *game)
{
	if (game->map)
	{
		if (game->map->no_texture)
			printf(RED"NO:"RESET"%s\n", game->map->no_texture);
		if (game->map->so_texture)
			printf(RED"SO:"RESET"%s\n", game->map->so_texture);
		if (game->map->ea_texture)
			printf(RED"EA:"RESET"%s\n", game->map->ea_texture);
		if (game->map->we_texture)
			printf(RED"WE:"RESET"%s\n", game->map->we_texture);
		if (game->map->ceiling_color)
			printf(GREEN"Ceiling:"RESET RED"R:"RESET"%d"RED"G:"RESET"%d"RED"B:" \
			RESET"%d\n", game->map->ceiling_color[0], game->map->ceiling_color[1],
				game->map->ceiling_color[2]);
		if (game->map->floor_color)
			printf(GREEN"Floor"RESET RED"R:"RESET"%d"RED"G:"RESET"%d"RED"B:" \
			RESET"%d\n", game->map->floor_color[0], game->map->floor_color[1],
				game->map->floor_color[2]);
		if (game->map->grid)
		{
			for(int i = 0; game->map->grid[i]; i++)
				printf(GREEN"%s\n"RESET, game->map->grid[i]);
		}
	}
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (checking_map(ac, av, game))
		return (free_game(game), EXIT_FAILURE);	
	if (game->map)
		print_map_details(game);
	return (free_game(game), EXIT_SUCCESS);
}