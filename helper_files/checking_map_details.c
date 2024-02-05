/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map_details.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnavidd <nnavidd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:24:19 by nnavidd           #+#    #+#             */
/*   Updated: 2023/06/06 20:29:55 by nnavidd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	check_wall(t_game *game, char *line, int line_no)
{
	if ((line_no + 1) == 1 || line_no == game->map.rows - 1)
	{
		while(*line)
		{
			if(*line != '1')
			{
				close_game(game);
				error_happend("MAWAL", -1);
			}
			line++;
		}
	}
	else
	{
		if (line[0] != '1' || line[game->map.columns - 1] != '1')
		{
			close_game(game);
			error_happend("MAWAL", -1);
		}
	}
	return ;
}

void	create_template_map(t_game *game,char *av)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		error_happend("MPADD", errno);
	line = get_next_line(fd);
	i = 0;
	game->map.map = (char **)ft_calloc((game->map.rows + 1), sizeof(char *));
	if (!game->map.map)
		return (free(line), close(fd), error_happend("MALOC", errno));
	while(line)
	{
		line[ft_strlen(line) - 1] = '\0';
		game->map.map[i] = ft_strdup(line);
		check_wall(game, line, i);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	game->map.map[i] = '\0';
	if(line)
		free(line);
	close(fd);
}

void	counting_map_lines(t_game *game, char *av)
{
	int		fd;
	char	*line;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		error_happend("MPADD", errno);
	game->map.rows = 0;
	game->map.columns = 0;
	line = get_next_line(fd);
	game->map.columns = ft_strlen(line) - 1;
	while (line)
	{
		game->map.rows += 1;
		free(line);
		line = get_next_line(fd);
		if (line && ((int)ft_strlen(line) - 1) != game->map.columns)
			return (free(line), close(fd), error_happend("MALSW", -1));
	}
	if (game->map.rows < 4 || game->map.rows == game->map.columns)
		return (close(fd), error_happend("MAROW", -1));
	close(fd);
}
	// ft_printf("rows:%d columns:%d\n", game->map.rows, game->map.columns);
	// write(1, "hiI\n", 4);
void	gathering_map_components(t_game *game)
{
	int	i;
	int j;

	j = 0;
	while (game->map.map[++j])
	{
		i = 0;
		while(game->map.map[j][++i])
		{
			if (game->map.map[j][i] == 'C')
				game->map.collectibles+= 1;
			else if (game->map.map[j][i] == 'E')
				game->map.exit +=1;
			else if (game->map.map[j][i] == 'P')
			{
				game->map.player += 1;
				game->xy = (t_pp){i,j, 0, 0, 0, 0};
			}
			else if (game->map.map[j][i] != '0' && game->map.map[j][i] != '1')
				return (free_ptr(game->map.map), error_happend("MACWR", -1));
		}
	}
	if (game->map.exit != 1 || game->map.player != 1 || game->map.collectibles < 1)
		return (free_ptr(game->map.map), error_happend("MAEPW", -1));
}
