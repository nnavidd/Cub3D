/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:36 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/13 21:01:37 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

size_t	array_length(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL || !*array)
		return (0);
	while(array[i])
		i++;
	return (i);
}

int check_map(t_parse *parser)
{
	(void)parser;
	return (0);
}

bool check_element(t_map *map)
{
	int	fd;

	if ((map->no_texture && (fd = open(map->no_texture, O_RDONLY)) < 0) &&
		(map->so_texture && (fd = open(map->so_texture, O_RDONLY)) < 0) &&
		(map->ea_texture && (fd = open(map->ea_texture, O_RDONLY)) < 0) &&
		(map->we_texture && (fd = open(map->we_texture, O_RDONLY)) < 0) &&
		((map->ceiling_color[0] != -1) && (map->ceiling_color[1] != -1) &&
		(map->ceiling_color[02] != -1)) && ((map->floor_color[0] != -1) &&
		(map->floor_color[1] != -1) && (map->floor_color[2] != -1)))
		{
			printf("check element is true\n");
			return (close(fd), true);
		}
	printf("check element is false\n");
	return (false);
}

bool assessment_element(t_map *map, int error)
{
	int	fd;
	int	i;

	if (!map->no_texture || (fd = open(map->no_texture, O_RDONLY)) < 0)
		return (error_handler("NO_texture file add wrong", error), false);
	if (!map->so_texture || (fd = open(map->so_texture, O_RDONLY) < 0))
		return (error_handler("SO_texture file add wrong", error), false);
	if (!map->ea_texture || (fd = open(map->ea_texture, O_RDONLY) < 0))
		return (error_handler("EA_texture file add wrong", error), false);
	if (!map->we_texture || (fd = open(map->we_texture, O_RDONLY) < 0))
		return (error_handler("WE_texture file add wrong", error), false);
	close(fd);
	i = 0;
	while (map->ceiling_color[i])
	{
		printf("color ceiling:[%d]:%d\n", i, map->ceiling_color[i]);
		if (map->ceiling_color[i++] == -1)
		{
			return (error_handler("Ceiling color is wrong", error), false);
		}	
	}
	i = 0;
	while (map->floor_color[i])
	{
		printf("color floor:[%d]:%d\n", i, map->floor_color[i]);
		if (map->floor_color[i++] == -1)	
			return (error_handler("Floor color is wrong", error), false);
	}
	return (true);
}

int	check_digit(int color)
{
	if (color < 0 || color > 255)
	{
		return (-1);
	}
	return (color);
}

int extract_rgb(t_parse *parser)
{
	char	**rgb;

	rgb = ft_split(parser->split[1], ',');
	if (array_length(rgb) != 3)
		return (free_2d_str(rgb), 1);
	if (!ft_strcmp(parser->split[0], "F"))
	{
		if (ft_atoi(rgb[0]))
		parser->map->floor_color[0] = check_digit(ft_atoi(rgb[0]));
		parser->map->floor_color[1] = check_digit(ft_atoi(rgb[1]));
		parser->map->floor_color[2] = check_digit(ft_atoi(rgb[2]));
	}
	else if (!ft_strcmp(parser->split[0], "C"))
	{
		parser->map->ceiling_color[0] = check_digit(ft_atoi(rgb[0]));
		parser->map->ceiling_color[1] = check_digit(ft_atoi(rgb[1]));
		parser->map->ceiling_color[2] = check_digit(ft_atoi(rgb[2]));
	}
	return (free_2d_str(rgb), 0);
}

int	read_element(t_parse *parser)
{
	if (parser->split[1])
	{
		if (array_length(parser->split) > 2)
			return (1);
		if (ft_strcmp(parser->split[0] ,"NO") == 0)
			parser->map->no_texture = ft_strdup(parser->split[1]);
		else if (ft_strcmp(parser->split[0], "SO") == 0)
			parser->map->so_texture = ft_strdup(parser->split[1]);
		else if (ft_strcmp(parser->split[0], "EA") == 0)
			parser->map->ea_texture = ft_strdup(parser->split[1]);
		else if (ft_strcmp(parser->split[0], "WE") == 0)
			parser->map->we_texture = ft_strdup(parser->split[1]);
		else if (ft_strcmp(parser->split[0], "F") == 0|| 
					ft_strcmp(parser->split[0], "C") == 0)
			extract_rgb(parser);
	}
	if (check_element(parser->map))
	{
		printf("assessif\n");
		parser->map_part = true;
		parser->details_part = false;
	}
		
	return (0);
}

void remove_char(char *str, char ch)
{
    char *src;
    char *dst;

	src = str;
	dst = str;
    if (str == NULL)
        return;
    while (*src != '\0')
	{
        if (*src != ch)
            *dst++ = *src;
        src++;
    }
    *dst = '\0';
}

char **remove_empty_elements(char **str_array)
{
	int 	i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	while (str_array[j] != NULL)
	{
		if (str_array[j++][0] != '\0')
			i++;
	}
	result = (char **)malloc((i + 1) * sizeof(char *));
	if (result == NULL)
		return NULL;
	i = -1;
	j = 0;
	while (str_array[++i] != NULL)
	{
		if (str_array[i][0] != '\0')
			result[j++] = str_array[i];
		else
			free(str_array[i]);
	}
	result[j] = NULL;
	return (free(str_array), result);
}

bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(WHITSPACE, line[i++]))
			return (false);
	}
	return (true);
}

int	fetch_map_detail(t_parse *parser, t_game *game, char *file)
{
	int li = 0;
	
	initiate_parse_variable(parser, game, file);
	while ((parser->line = get_next_line(parser->fd)))
	{
		li++;
		if (parser->line[ft_strlen(parser->line) -1] == '\n')
			parser->line[ft_strlen(parser->line) - 1] = '\0';
		if (!parser->line)
			continue ;
		if (!line_is_empty(parser->line))
		{
			parser->split = ft_split(parser->line, ' ');
			for (int j = 0; parser->split[j] != NULL; j++)
				remove_char(parser->split[j], '\t');
			parser->split = remove_empty_elements(parser->split);
			if (parser->details_part)
				read_element(parser);
			if (parser->map_part)
				check_map(parser);
			// for(int i = 0; parser->split[i]; i++)
			// 	printf("\ts[%d]:%s.\n", i, parser->split[i]);
			free_2d_str(parser->split);
		}
		if (parser->line)
			free(parser->line);
	}
	close(parser->fd);
	return (EXIT_SUCCESS);
}

int	parsing_map(t_game *game, char *file)
{
	t_parse	*parser;

	parser = (t_parse *)ft_calloc(1, sizeof(t_parse));
	initiate_map_variable(game);
	fetch_map_detail(parser, game, file);
	assessment_element(parser->map, NOSYSERR);
	free(parser);
	return (EXIT_SUCCESS);
}

int	check_map_file_format_add(char *file)
{
	char	*str;
	int		i;
	int		j;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_handler("MPADD", SYSERR));
	close(fd);
	str = ft_strdup(".cub\0");
	i = (int)ft_strlen(file) - 4;
	j = 0;
	if (i < 0)
		return (free(str), error_handler("MAFOR", NOSYSERR));	
	while (file[i] != '\0' && str[j] != '\0')
	{
		if (file[i++] != str[j++])
			return (free(str), error_handler("MAFOR", NOSYSERR));
	}
	if (file[i] == '\0' && str[j] == '\0')
		return (free(str), EXIT_SUCCESS);
	else
		return (free(str), error_handler("MAFOR", NOSYSERR)); 
}

int	checking_map(int ac, char **av, t_game *game)
{
	if (ac != 2)
		return (EXIT_FAILURE); /// The error should be handled.
	if (check_map_file_format_add(av[1]))
		return (EXIT_FAILURE); // The error should be handled.
	if (parsing_map(game, av[1]))
		return (EXIT_FAILURE); /// The error should be handled.
	return (EXIT_SUCCESS);
}