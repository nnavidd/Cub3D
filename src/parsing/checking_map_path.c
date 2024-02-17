/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:23:22 by nnavidd           #+#    #+#             */
/*   Updated: 2024/02/17 01:29:24 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

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
	if (write(1,"\n",1) < 0)
        return ;
}

char	**creat_sample_gird(t_game *game)
{
	char	**grid;
	int		i;

	grid = (char **) ft_calloc(game->map->map_height + 1, sizeof(char *));
	if (!grid)
		return (error(game, "Malloc error!!!", SYSERR), NULL);
	i = -1;
	while(game->map->grid[++i] != 0)
		grid[i] = ft_strdup(game->map->grid[i]);
	grid[i] = '\0';
	return (grid);
}

bool fill_grid(t_game *game, t_pos pos, char **grid)
{
    printf("x:%d width:%d and y:%d height:%d\n", pos.x, game->map->widths[pos.x], pos.y, game->map->map_height);
    if (pos.y >= game->map->widths[pos.x] || pos.x >= game->map->map_height)
        return (false);
            // return (error(game, "Map path is wrong!!!", NOSYSERR), false);
    if (game->map->grid[pos.x][pos.y] == '1')
        return (true);
    // if (grid[pos.y][pos.x] == 'C')
        // game->ply.check_coin += 1;
    // if (grid[pos.y][pos.x] == 'E')
        // game->ply.check_exit += 1;
    if (game->map->grid[pos.x][pos.y] == ' ')
        game->map->grid[pos.x][pos.y] = '0';
    if (fill_grid(game, (t_pos){pos.x + 1, pos.y}, grid))
        return (true);
    if (fill_grid(game, (t_pos){pos.x - 1, pos.y}, grid))
        return (true);
    if (fill_grid(game, (t_pos){pos.x, pos.y + 1}, grid))
        return (true);
    if (fill_grid(game, (t_pos){pos.x, pos.y - 1}, grid))
        return (true);
    return (true);
}

/*To check the path we need to create a sample map
of the taken map to check if the created floor
goes to exit part and all coins or not.*/
int check_map_path(t_game *game)
{
    char **grid;

    grid = creat_sample_gird(game);
    if (!fill_grid(game, game->ply.pos, grid))
        return (free_array(grid), error(game, "Map has wrong path!!!", NOSYSERR));
    free_array(grid);
    return (0);
}
