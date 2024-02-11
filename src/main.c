/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:16:02 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/11 11:58:54 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	initiate_map_variable(t_game *game)
{
	game->map = (t_map *)ft_calloc(1, sizeof(t_map));
	game->map->resolution_x = 0;
	game->map->resolution_y = 0;
	game->map->no_texture = NULL;
	game->map->so_texture = NULL;
	game->map->ea_texture = NULL;
	game->map->we_texture = NULL;
	game->map->floor_color[0] = 0;
	game->map->ceiling_color[0] = 0;
	game->map->grid = NULL;
	game->map->map_width = 0;
	game->map->map_height = 0;
}

void	free_map_grid(char **map)
{
	char	**tmp;

	tmp = map;
	if (*tmp)
	{
		while(*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(map);
	}	
}

void	free_game(t_game *game)
{
	
	if(game == NULL || game->map == NULL)
		return ;
	if(game->map->no_texture != NULL)
	printf("hi\n");
		free(game->map->no_texture);
	if(game->map->so_texture != NULL)
		free(game->map->so_texture);
	if(game->map->ea_texture != NULL)
		free(game->map->ea_texture);
	if(game->map->we_texture != NULL)
		free(game->map->we_texture);
	if(game->map->grid != NULL)
		free_map_grid(game->map->grid);
	if(game->map != NULL)
		free(game->map);
	free(game);
}


int	fetch_map_detail(t_game *game, char *file)
{
	int		fd;
	char	*line;
	// int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_handler("MPADD", errno);
	(void)game;
	line = get_next_line(fd);
	// i = 0;
	// game->map->grid = (char **)ft_calloc((game->map.rows + 1), sizeof(char *));
	// if (!game->map.map)
		// return (free(line), close(fd), error_happend("MALOC", errno));
	while(line)
	{
		// line[ft_strlen(line) - 1] = '\0';
		// game->map.map[i] = ft_strdup(line);
		// check_wall(game, line, i);
		// free(line);
		// i++;
		// line = get_next_line(fd);
	}
	// game->map.map[i] = '\0';
	if(line)
		free(line);
	close(fd);
	return(EXIT_SUCCESS);
}

int	parsing_map(t_game *game, char *file)
{
	initiate_map_variable(game);
	(void)file;
	fetch_map_detail(game, file);
	return (EXIT_SUCCESS);
}

int	check_map_file_format(char *file)
{
	char	*str;
	int		i;
	int		j;

	str = ft_strdup(".ber\0");
	i = (int)ft_strlen(file) - 4;
	j = 0;

	if (i < 0)
		return (free(str), EXIT_FAILURE);	
	while (file[i] != '\0' && str[j] != '\0')
	{
		printf("file[%d]: %c\n", i, file[i]);
		if (file[i++] != str[j++])
			return (free(str), EXIT_FAILURE);
	}
	printf("file[%d]: %c and str[%d]: %c\n", i, file[i], j, str[j]);
	if (file[i] == '\0' && str[j] == '\0')
		return (free(str), EXIT_SUCCESS);
	else
		return (free(str), EXIT_FAILURE); 
}

int	checking_map(int ac, char **av, t_game *game)
{
	if(ac != 2)
		return (EXIT_FAILURE); /// The error should be handled.
	if(check_map_file_format(av[1]))
		return (EXIT_FAILURE); // The error should be handled.
	if(parsing_map(game, av[1]))
		return (EXIT_FAILURE); /// The error should be handled.
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if(checking_map(ac, av, game))
		return (free_game(game), EXIT_FAILURE);	
	if (game->map)
	{
		game->map->map_height = 203;
		printf("hi the map_hight is:%d\n", game->map->map_height);
		exit(1);
	}
	return (free_game(game), EXIT_SUCCESS);
}