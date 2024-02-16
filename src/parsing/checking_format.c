/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:36 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/16 16:23:44 by nnabaeei         ###   ########.fr       */
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
bool	all_chr_present(char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while(s2[j])
		{
			if (s1[i] == s2[j])
				break;
			j++;
		}
		if (s1[i] != s2[j])
			return (false);
		i++;
	}
	return (true);
}
/* This function reallocate an array of string from its old size to its
 new size.*/
uint32_t *ft_realloc_int(uint32_t *input, size_t old_count, size_t new_count)
{
	uint32_t	*new_ptr;
	size_t		i;

	if (!input)
	{
		new_ptr = (uint32_t *)ft_calloc(new_count + 1, sizeof(uint32_t));
		if (!new_ptr)
			return NULL;
		return (new_ptr);
	}

	new_ptr = (uint32_t *)ft_calloc(new_count + 1, sizeof(uint32_t));
	if (!new_ptr)
		return (free(input),NULL);
	i = -1;
	while (++i < old_count)
		new_ptr[i] = input[i];
	free(input);
	return new_ptr; // Return the new memory block
}

char	**ft_realloc_strings(char **ptr, size_t old_count, size_t new_count)
{
	char	**new_ptr;
	size_t	i;

	if (!ptr)
	{
		new_ptr = (char **) ft_calloc(new_count + 1, sizeof(char *));
		if (!new_ptr)
			return (free_array(new_ptr), NULL);
		return (new_ptr);
	}
	new_ptr = ft_calloc(old_count + new_count + 1, sizeof(char *));
	if (new_ptr == NULL)
		return (free_array(ptr), NULL);
	i = -1;
	while (++i < old_count)
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		if (new_ptr[i] == NULL)
			return (free_array(new_ptr), NULL);
	}
	free_array(ptr);
	return (new_ptr);
}
size_t list_len(uint32_t *arr)
{
	size_t	count;

	count = 0;
	while (arr && *arr)
	{
		count++;
		arr++;
	}
	return (count);
}

int read_map(t_parse *parser)
{
	
	// (void)parser;
	t_map	*m;

	m = parser->map;
	if (!all_chr_present(parser->line, MAPCHRS))
	{
		parser->map_part = false;	
		return (error_handler("Map chars are incorrect!", NOSYSERR), 1);
	}
	
	m->grid = ft_realloc_strings(m->grid, array_length(m->grid), \
				array_length(m->grid) + 1);
	m->grid[m->map_height] = ft_strdup(parser->line);
	m->grid[++m->map_height] = '\0';
	return (0);
}

bool check_element(t_parse *parser)
{
	int		fd;
	t_map	*map;

	map = parser->map;
	if ((map->no_texture && (fd = open(map->no_texture, O_RDONLY)) > 0) &&
		(map->so_texture && (fd = open(map->so_texture, O_RDONLY)) > 0) &&
		(map->ea_texture && (fd = open(map->ea_texture, O_RDONLY)) > 0) &&
		(map->we_texture && (fd = open(map->we_texture, O_RDONLY)) > 0) &&
		((map->ceiling_color[0] != -1) && (map->ceiling_color[1] != -1) &&
		(map->ceiling_color[02] != -1)) && ((map->floor_color[0] != -1) &&
		(map->floor_color[1] != -1) && (map->floor_color[2] != -1)))
		{
			// printf("check element is true line is: %s\n", parser->line);
			return ( true);
		}
	// printf("check element is false\n");
	return (false);
}

int	check_map_char(t_map *map)
{
	
}

int	calc_map_rows_widths(t_map *map)
{
	uint32_t	i;
	uint32_t	longest;

	i = -1;
	longest = 0;
	map->widths = (uint32_t *)ft_calloc(map->map_height + 1, sizeof(uint32_t));
	while (++i < map->map_height)
	{
		map->widths[i] = ft_strlen(map->grid[i]);
		if (longest < map->widths[i])
			longest = map->widths[i];
	}
	map->max_width = longest;
	for (int i = 0; map->widths[i]; i++)
		printf("line[%d]: length:[%d]	|%s|\n", i, map->widths[i], map->grid[i]);
	printf(GREEN"longest line is: "RESET RED"%d\n"RESET, map->max_width);
	return (0);
}

bool assessment_map(t_map *map)
{
	// printf("hight:%d, line[%d]:%s\n", m->map_height, m->map_height, m->grid[m->map_height]);
	calc_map_rows_widths(map);
	check_map_char(map);
	
	return (true);
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
		// printf("color ceiling:[%d]:%d\n", i, map->ceiling_color[i]);
		if (map->ceiling_color[i++] == -1)
			return (error_handler("Ceiling color is wrong", error), false);
	}
	i = 0;
	while (map->floor_color[i])
	{
		// printf("color floor:[%d]:%d\n", i, map->floor_color[i]);
		if (map->floor_color[i++] == -1)	
			return (error_handler("Floor color is wrong", error), false);
	}
	return (true);
}

bool is_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			// printf("string color:%s\n", str);
			return (false);
		}
		i++;
	}
	return (true);
}

int	check_digit(char  *color)
{
	if (!is_numeric(color))
		return (-1);
	if (ft_atoi(color) < 0 || ft_atoi(color) > 255)
	{
		// printf("is not a in a range:%d\n", ft_atoi(color));
		return (-1);
	}
	// printf("the color num:%d\n", ft_atoi(color));
	return (ft_atoi(color));
}

void str_trim(char *str, char ch)
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

char **rm_empty_array_elements(char **str_array)
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

int extract_rgb(t_parse *parser)
{
	char	**rgb;

	rgb = ft_split(parser->split[1], ',');
	// for (int  i =  0; rgb[i]; i++)
	// 	printf("rgb[%d]:%s\n", i, rgb[i]);
	if (array_length(rgb) != 3)
		return (free_array(rgb), 1);
	if (!ft_strcmp(parser->split[0], "F"))
	{
		parser->map->floor_color[0] = check_digit(rgb[0]);
		parser->map->floor_color[1] = check_digit(rgb[1]);
		parser->map->floor_color[2] = check_digit(rgb[2]);
	}
	else if (!ft_strcmp(parser->split[0], "C"))
	{
		parser->map->ceiling_color[0] = check_digit(rgb[0]);
		parser->map->ceiling_color[1] = check_digit(rgb[1]);
		parser->map->ceiling_color[2] = check_digit(rgb[2]);
	}
	return (free_array(rgb), 0);
}

int	read_element(t_parse *parser)
{
	parser->split = ft_split(parser->line, ' ');
	for (int j = 0; parser->split[j] != NULL; j++)
		str_trim(parser->split[j], '\t');
	parser->split = rm_empty_array_elements(parser->split);
	if (array_length(parser->split) != 2)
		return (free_array(parser->split), 1);
	if (ft_strcmp(parser->split[0] ,"NO") == 0)
		parser->map->no_texture = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "SO") == 0)
		parser->map->so_texture = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "EA") == 0)
		parser->map->ea_texture = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "WE") == 0)
		parser->map->we_texture = ft_strdup(parser->split[1]);
	else if (ft_strcmp(parser->split[0], "F") == 0 || 
				ft_strcmp(parser->split[0], "C") == 0)
		extract_rgb(parser);
	return (free_array(parser->split), 0);
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

int	fetch_map_detail(t_parse *parser)
{
	int li = 0;
	
	while ((parser->line = get_next_line(parser->fd)))
	{
		li++;
		if (parser->line[ft_strlen(parser->line) -1] == '\n')
			parser->line[ft_strlen(parser->line) - 1] = '\0';
		if (!parser->line)
			continue ;
		if (!line_is_empty(parser->line))
		{

			if (check_element(parser))
				read_map(parser);
			read_element(parser);
			// for(int i = 0; parser->split[i]; i++)
			// 	printf("\ts[%d]:%s.\n", i, parser->split[i]);
		}
		if (parser->line)
			free(parser->line);
	}
	close(parser->fd);
	return (EXIT_SUCCESS);
}

void	initiate_game(t_game *game, char *file)
{
	game->parser = (t_parse *)ft_calloc(1, sizeof(t_parse));
	game->map = (t_map *)ft_calloc(1, sizeof(t_map));
	initiate_map(game->map);
	initiate_parser(game->parser, game, file);
}

int	parsing_map(t_game *game, char *file)
{
	initiate_game(game, file);
	fetch_map_detail(game->parser);
	assessment_element(game->map, NOSYSERR);
	assessment_map(game->map);
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