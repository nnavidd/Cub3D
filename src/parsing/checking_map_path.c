/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:23:22 by nnavidd           #+#    #+#             */
/*   Updated: 2023/06/02 20:03:22 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

/*This func calls nowhere, just created to
check the created sample map.*/
void print_gird(char **grid)
{
	int	i = 0;

	while (grid[i] != NULL)
	{
		ft_printf("%d:%s\n",i, grid[i]);
		i++;
	}
	write(1,"\n",1);
}

char	**creat_sample_gird(t_game *game)
{
	char	**grid;
	int		i;

	grid = (char **) ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!grid)
		return (close_game(game), error_happend("MALOC", errno), NULL);
	i = 0;
	while(game->map.map[i] != 0)
	{
		grid[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	grid[i] = '\0';
	return (grid);
}

int fill_grid(t_game *game, t_pp pos, char **grid)
{
    if (grid[pos.y][pos.x] == '1')
        return 0;
    if (grid[pos.y][pos.x] == 'C')
        game->xy.check_coin += 1;
    if (grid[pos.y][pos.x] == 'E')
        game->xy.check_exit += 1;
    grid[pos.y][pos.x] = '1';
    fill_grid(game, (t_pp){pos.x + 1, pos.y, 0, 0, 0, 0}, grid);
    fill_grid(game, (t_pp){pos.x - 1, pos.y, 0, 0, 0, 0}, grid);
    fill_grid(game, (t_pp){pos.x, pos.y + 1, 0, 0, 0, 0}, grid);
    fill_grid(game, (t_pp){pos.x, pos.y - 1, 0, 0, 0, 0}, grid);
    if (game->xy.check_coin == game->map.collectibles && game->xy.check_exit == 1)
    {
        return (1);
    }
    return (0);
}

/*To check the path we need to create a sample map
of the taken map to check if the created floor
goes to exit part and all coins or not.*/
void check_map_path(t_game *game)
{
    char **grid;

    grid = creat_sample_gird(game);
    if (!fill_grid(game, game->xy, grid))
        return (free_ptr(grid), error_happend("MAWRG", -1));
    free_ptr(grid);
    game->xy.check_coin = 0;
}
