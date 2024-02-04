/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:18:31 by nnavidd           #+#    #+#             */
/*   Updated: 2023/06/02 20:05:35 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

/*This function calls xpm2win func to map the Map parts
with their initiated variables.*/
void	creat_graphical_map(t_game *game)
{
	t_pp	pos;

	pos.y = 0;
	while (pos.y < game->map.rows)
	{
		pos.x = 0;
		while (pos.x < game->map.columns)
		{
			if (game->map.map[pos.y][pos.x] == '1')
				addressing_xpm_to_window(game, game->pi.wall, pos);
			if (game->map.map[pos.y][pos.x] == 'C')
				addressing_xpm_to_window(game, game->pi.coin, pos);
			if (game->map.map[pos.y][pos.x] == 'P')
				addressing_xpm_to_window(game, game->pi.player_left, pos);
			if (game->map.map[pos.y][pos.x] == 'E')
				addressing_xpm_to_window(game, game->pi.exit, pos);
			if (game->map.map[pos.y][pos.x] == '0')
				addressing_xpm_to_window(game, game->pi.floor, pos);
			pos.x++;
		}
		pos.y++;
	}
}

/*This function changes the position of the player in the
map to shows it as moving.*/
int	move(t_game *game, int j, int i)
{
	int		x;
	int		y;

	x = game->xy.x;
	y = game->xy.y;
	if (game->map.map[y + j][x + i] != '1')
	{
		if (game->map.map[y + j][x + i] == 'E')
		{
		 	if (game->xy.check_coin == game->map.collectibles)
				return(write(1, "win!\n", 5), close_game(game));
				// return(win_message(game, "WIN"));
			else
				return (0);
		}
		if (game->map.map[y + j][x + i] == 'C')
			game->xy.check_coin++;
		game->map.map[y + j][x + i] = 'P';
		game->map.map[game->xy.y][game->xy.x] = '0';
		game->xy.x += i;
		game->xy.y += j;
		game->xy.steps++;
		usleep(DELAY);
		creat_graphical_map(game);
	}
	return (0);
}

/*some mlx function has a function as one of their arguments
that we can define into how we need to handle
the different situation regarding that mlx function. this function
handles different keys that would be pressed during the game.*/
int keyboard_key_press(int key, void *param)
{
	t_game *game;

	game = (t_game *)param;
	game->pi.key_state = 1;
	if (key == KEY_W || key == KEY_UP)
		game->pi.key = 'U';
	if (key == KEY_S || key == KEY_DOWN)
		game->pi.key = 'D';
	if (key == KEY_A || key == KEY_LEFT)
		game->pi.key = 'L';
	if (key == KEY_D || key == KEY_RIGHT)
		game->pi.key = 'R';
	if (key == Esc)
		close_game(game);
	return (0);
}

/*some mlx function has a function as one of their arguments
that we can define into how we need to handle
the different situation regarding that mlx function. this function
handles different keys that would be released during the game.*/
int keyboard_key_release(int key, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (key == KEY_W || key == KEY_UP)
		game->pi.key_state = 0;
	if (key == KEY_S || key == KEY_DOWN)
		game->pi.key_state = 0;
	if (key == KEY_A || key == KEY_LEFT)
		game->pi.key_state = 0;
	if (key == KEY_D || key == KEY_RIGHT)
		game->pi.key_state = 0;
	return (0);
}

/*mlx_loop_hook creates a loop to recall the used hook function,
in this function, the move func is called according to 
the triggered hooked function.*/
int continuous_movement(void *param)
{
	t_game *game;
	char	key;
	int		status;

	game = (t_game *)param;
	key = game->pi.key;
	status = game->pi.key_state;
	if(game->xy.first_step != game->xy.steps)
	{
		game->xy.first_step = game->xy.steps;
		ft_printf("steps:%d\n", game->xy.steps);
	}
	if (key == 'U' && status)
		move(game, -1, 0);
	else if (key == 'D' && status)
		move(game, 1, 0);
	else if (key == 'L' && status)
		move(game, 0, -1);
	else if (key == 'R' && status)
		move(game, 0, 1);
	return (0);

}

// void win_message(t_game *game, char *message)
// {
// 	int		x;
// 	int		y;
// 	if (message[0] == 'W')
// 	{
// 		x = (game->map.columns / 2) * PIX;
// 		y = (game->map.rows / 2) * PIX;
// 		game->msg.color1 = 0xFF0000;
// 	}
// 	mlx_string_put(game->mlx.mlx , game->mlx.win, x, y, game->msg.color1, "You won!!!");
// 	// ft_printf("You won!!!\n");
// }
