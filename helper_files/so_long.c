/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:11:39 by nnavidd           #+#    #+#             */
/*   Updated: 2023/06/04 23:11:22 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

/*This fucntion use mlx fuction to declares the map parts' variables
with thier related xpm files.*/
void	addressing_picesimage_with_xpmfile(t_game *game, int *w, int *h)
{
	game->pi.wall = mlx_xpm_file_to_image(game->mlx.mlx, Wall, w, h);
	if (game->pi.wall == NULL)
		return (error_happend("XPMWA", -1));
	game->pi.coin = mlx_xpm_file_to_image(game->mlx.mlx, Coin, w, h);
	if (game->pi.coin == NULL)
		return (error_happend("XPMCO", -1));
	game->pi.floor = mlx_xpm_file_to_image(game->mlx.mlx, Floor, w, h);
	if (game->pi.floor == NULL)
		return (error_happend("XPMWA", -1));
	game->pi.exit = mlx_xpm_file_to_image(game->mlx.mlx, Exit, w, h);
	if (game->pi.exit == NULL)
		return (error_happend("XPMEX", -1));
	game->pi.player_up = mlx_xpm_file_to_image(game->mlx.mlx, P_U, w, h);
	if (game->pi.player_up == NULL)
		return (error_happend("XPMPL", -1));
	game->pi.player_down = mlx_xpm_file_to_image(game->mlx.mlx, P_D, w, h);
	if (game->pi.player_down == NULL)
		return (error_happend("XPMPL", -1));
	game->pi.player_left = mlx_xpm_file_to_image(game->mlx.mlx, P_L, w, h);
	if (game->pi.player_left == NULL)
		return (error_happend("XPMPL", -1));
	game->pi.player_right = mlx_xpm_file_to_image(game->mlx.mlx, P_R, w, h);
	if (game->pi.player_right == NULL)
		return (error_happend("XPMPL", -1));
}

/*This function use mlx function to shows the created xpm files on the screen.*/
void	addressing_xpm_to_window(t_game *game, void *part, t_pp pos)
{
	int		width;
	int		hight;
	char	*itoa;
	char	*steps;

	width = pos.x * PIX;
	hight = pos.y * PIX;
	itoa = ft_itoa(game->xy.steps);
	steps = ft_strjoin("STEPS:", itoa);
	if (game->map.map[pos.y][pos.x] == 'P' && game->pi.key == 'U')
		part = game->pi.player_up;
	if (game->map.map[pos.y][pos.x] == 'P' && game->pi.key == 'D')
		part = game->pi.player_down;
	if (game->map.map[pos.y][pos.x] == 'P' && game->pi.key == 'L')
		part = game->pi.player_left;
	if (game->map.map[pos.y][pos.x] == 'P' && game->pi.key == 'R')
		part = game->pi.player_right;
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, part, width, hight);
	mlx_string_put(game->mlx.mlx , game->mlx.win, 10, 10, 0xFF1234, steps);
	free(itoa);
	free(steps);
}

/*Calling mlx tools in the porject.*/
void mlx_tools(t_game *game)
{
	int	width;
	int	hight;

	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		return(close_game(game),error_happend("MLXIN", errno));
	game->mlx.win = mlx_new_window(game->mlx.mlx, game->map.columns * PIX, game->map.rows * PIX, "so_long");
	if (!game->mlx.win)
		return(close_game(game),error_happend("MLXWI", errno));
	addressing_picesimage_with_xpmfile(game, &width, &hight);
	creat_graphical_map(game);
	mlx_hook(game->mlx.win, DestroyNotify, StructureNotifyMask, close_game, game);
	mlx_hook(game->mlx.win, KeyPress, KeyPressMask, keyboard_key_press, game);
	mlx_hook(game->mlx.win, KeyRelease, KeyReleaseMask, keyboard_key_release, game);
	mlx_loop_hook(game->mlx.mlx, continuous_movement, game);
	mlx_loop(game->mlx.mlx);
}

/*calling different function to check the details 
of the taken map.ber file.*/
void	check_map_detail(t_game *game, char *av)
{
	initiate_game_variable(game);
	counting_map_lines(game, av);
	create_template_map(game, av);
	gathering_map_components(game);
	check_map_path(game);
	// print_map_details(game);
}

int main (int ac, char **av)
{
	t_game	game;
	
	check_main_arguments(ac, av);
	check_map_detail(&game, av[1]);
	mlx_tools(&game);
	close_game(&game);
	return (0);
}
	// write(1, "hi\n", 3);
	// system("leaks so_long");
