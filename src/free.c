/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:06:42 by nnavidd           #+#    #+#             */
/*   Updated: 2023/05/31 13:32:50 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

/*Freeing the array of strings*/
void	free_ptr(char **str)
{
	char	**tmp;

	tmp = str;
	while (*str != 0)
	{
		if (*str != NULL)
		{
			free(*str);
			*str = NULL;
		}
		str++;
	}
	free(tmp);
	tmp = NULL;
}

/*calling the xml func to destroy the created images*/
void	destroy_pices_xpm(t_game *game)
{
	if (game->pi.wall)
		mlx_destroy_image(game->mlx.mlx, game->pi.wall);
	if (game->pi.floor)
		mlx_destroy_image(game->mlx.mlx, game->pi.floor);
	if (game->pi.player_up)
		mlx_destroy_image(game->mlx.mlx, game->pi.player_up);
	if (game->pi.player_down)
		mlx_destroy_image(game->mlx.mlx, game->pi.player_down);
	if (game->pi.player_left)
		mlx_destroy_image(game->mlx.mlx, game->pi.player_left);
	if (game->pi.player_right)
		mlx_destroy_image(game->mlx.mlx, game->pi.player_right);
	if (game->pi.coin)
		mlx_destroy_image(game->mlx.mlx, game->pi.coin);
	if (game->pi.exit)
		mlx_destroy_image(game->mlx.mlx, game->pi.exit);
}

int	close_game(t_game *game)
{
	mlx_loop_end(game->mlx.mlx);
	destroy_pices_xpm(game);
	if (game->mlx.win)
	{
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
		game->mlx.win = NULL;
	}
	if (game->mlx.mlx)
	{
		mlx_destroy_display(game->mlx.mlx);
		game->mlx.mlx = NULL;
	}
	free_ptr(game->map.map);
	exit(EXIT_FAILURE);
	return (0);
}

// void	free_game_map(t_game *game)
// {
// 	int i;

// 	if (game->map.map != NULL)
// 	{
// 		i = 0;
// 		while (game->map.map[i])
// 		{
// 			if (game->map.map[i] != NULL)
// 			{
// 				free(game->map.map[i]);
// 				game->map.map[i] = NULL;
// 			}
// 			i++;
// 		}
// 		free(game->map.map);
// 		game->map.map = NULL;
// 	}
// }
