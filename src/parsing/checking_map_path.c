/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 21:23:22 by nnavidd           #+#    #+#             */
/*   Updated: 2024/02/17 20:54:55 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

/*This func calls nowhere, just created to
check the created sample map.*/
void print_grid(char **grid)
{
	int	i = 0;

	while (grid[i] != NULL)
	{
		ft_printf(ORG"%d:%s|\n"RESET,i, grid[i]);
		i++;
	}
	if (write(1,"\n",1) < 0)
		return ;
}

char	**creat_sample_gird(t_game *game)
{
	char	**grid;
	int		i;

	grid = (char **) ft_calloc(game->map.map_height + 1, sizeof(char *));
	if (!grid)
		return (error(game, "Malloc error!!!", SYSERR), NULL);
	i = -1;
	while(game->map.grid[++i] != 0)
		grid[i] = ft_strdup(game->map.grid[i]);
	grid[i] = '\0';
	return (grid);
}

bool fill_grid(t_game *game, t_pos pos, char **grid)
{
    if ((int)pos.x < 0 || pos.x >= game->map.widths[pos.y] || (int)pos.y < 0 || pos.y >= game->map.map_height)
        return false;

    if (grid[pos.y][pos.x] != '1' && grid[pos.y][pos.x] != '0' && !ft_strchr("NEWS", grid[pos.y][pos.x]))
	{
		printf("hi p.xy:{%d, %d} width:%d height:%d\n", pos.x, pos.y, game->map.widths[pos.y], game->map.map_height);
        return false;
	}

    if (grid[pos.y][pos.x] == '-')
        return false; // Already visited

    grid[pos.y][pos.x] = '-'; // Mark the current position as visited

    sleep(1); // Add a delay
    print_grid(grid); // Print the grid

    fill_grid(game, (t_pos){pos.x - 1, pos.y}, grid);
    fill_grid(game, (t_pos){pos.x, pos.y + 1}, grid);
    fill_grid(game, (t_pos){pos.x + 1, pos.y}, grid);
    fill_grid(game, (t_pos){pos.x, pos.y - 1}, grid);

    return true;
}

/*To check the path we need to create a sample map
of the taken map to check if the created floor
goes to exit part and all coins or not.*/
int check_map_path(t_game *game)
{
	char **grid;

	grid = creat_sample_gird(game);
	// exit(1);
	if (!fill_grid(game, game->ply.pos, grid))
		printf("path is wrong!!!\n");
		// return (free_array(grid), error(game, "Map has wrong path!!!", NOSYSERR));
	free_array(grid);
	return (0);
}
