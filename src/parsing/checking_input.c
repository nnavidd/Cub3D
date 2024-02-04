/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:14:58 by nnavidd           #+#    #+#             */
/*   Updated: 2023/06/02 19:42:46 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	initiate_game_variable(t_game *game)
{
	game->map.map = NULL;
    game->map.rows = 0;
    game->map.columns = 0;
    game->map.collectibles = 0;
    game->map.exit = 0;
    game->map.player = 0;
    game->mlx.mlx = NULL;
    game->mlx.win = NULL;
    game->xy.x = 0;
    game->xy.y = 0;
    game->xy.check_coin = 0;
    game->xy.check_exit = 0;
    game->xy.steps = 0;
    game->xy.first_step = 0;
    game->pi.wall = NULL;
    game->pi.coin = NULL;
    game->pi.floor = NULL;
    game->pi.exit = NULL;
    game->pi.player_up = NULL;
    game->pi.player_down = NULL;
    game->pi.player_left = NULL;
    game->pi.player_right = NULL;
    game->pi.width = 0;
    game->pi.hight = 0;
    game->pi.key = 0;
    game->pi.key_state = 0;
}
	// ft_memset(game, 0, sizeof(t_game));

int	check_map_file_format(char **av)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strdup(".ber");
	i = ft_strlen(av[1]) - 4;
	j = 0;
	while (av[1][i] != '\0' && str[j] != '\0')
	{
		if (av[1][i] != str[j])
			return (free(str), 0);
		i++;
		j++;
	}
	if (av[1][i] == '\0' && str[j] == '\0')
		return (free(str), 1);
	else
		return (free(str), 0);
}

int	check_main_arguments(int ac, char **av)
{
	if (ac == 0 || ac != 2)
		error_happend("INPUT", -1);
	if (!check_map_file_format(av))
		error_happend("MAFOR", 1);
	// (*game)->map = av;
	return (0);
}

/*This func calls nowhere, just used during writing
project to check the map details.*/
void	print_map_details(t_game *game)
{
	int i;

	i = 0;
	while (game->map.map[i])
	{
		ft_printf("%d:%s\n", i, game->map.map[i]);
		i++;
	}
	ft_printf("\nAmount of Player: %d Exit: %d Collectable: %d\n", game->map.player, game->map.exit, game->map.collectibles);
	ft_printf("the player is in Y%d : X%d\n", game->xy.y, game->xy.x);
	ft_printf("Rows:%d Columns:%d\n", game->map.rows, game->map.columns);
}
