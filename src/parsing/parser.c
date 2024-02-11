/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:45:15 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/11 12:12:02 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/parser.h>

int parse_resolution(char *line, t_map *map) 
{

}

int parse_texture(char *line, char **texture)
{
	*texture = ft_strdup(line + 3);
	if (!*texture) {
		perror("Error: Memory allocation failed"); //error handler should be applied.
		return (0);
	}
	return (1);
}

int parse_color(char *line, int color[3])
{

}

int parse_map(char *line, t_map *map, int *map_lines)
{
	int len;

	len = ft_strlen(line);
	map->grid[*map_lines] = malloc(len + 1);
	if (!map->grid[*map_lines])
	{
		perror("Error: Memory allocation failed"); //error handler should be applied.
		return (0);
	}
	ft_strcpy(map->grid[*map_lines], line);
	(*map_lines)++;
	return (1);
}

int parse_config(char *filename, t_map *map)
{
	char *line;
	size_t len;
	ssize_t read;
	int map_lines;

	line = NULL;
	len = 0;
	map_lines = 0;
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		perror("Error: Could not open file"); //error handler should be applied.
		return (0);
	}
	while ((read = getline(&line, &len, file)) != -1)
	{
		if (line[0] == 'R')
		{
			if (!parse_resolution(line, map))
			{
				fclose(file);
				free(line);
				return (0);
			}
		}
		else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		{
			char **texture = NULL;
			if (line[0] == 'N') texture = &map->no_texture;
			else if (line[0] == 'S') texture = &map->so_texture;
			else if (line[0] == 'W') texture = &map->we_texture;
			else if (line[0] == 'E') texture = &map->ea_texture;

			if (!parse_texture(line, texture))
			{
				fclose(file);
				free(line);
				return (0);
			}
		} 
		else if (line[0] == 'S')
		{
			if (!parse_texture(line, &map->sprite_texture))
			{
				fclose(file);
				free(line);
				return (0);
			}
		}
		else if (line[0] == 'F')
		{
			if (!parse_color(line, map->floor_color))
			{
				fclose(file);
				free(line);
				return (0);
			}
		}
		else if (line[0] == 'C')
		{
			if (!parse_color(line, map->ceiling_color))
			{
				fclose(file);
				free(line);
				return (0);
			}
		}
		else if (line[0] == '1' || line[0] == '0')
		{
			if (!parse_map(line, map, &map_lines))
			{
				fclose(file);
				free(line);
				return (0);
			}
		}
	}

	fclose(file);
	free(line);
	map->map_width = map_lines > 0 ? strlen(map->grid[0]) : 0;
	map->map_height = map_lines;
	return (1);
}

// void print_map(t_map *map)
// {
// 	printf("Resolution: %dx%d\n", map->resolution_x, map->resolution_y);
// 	printf("NO Texture: %s\n", map->no_texture);
// 	printf("SO Texture: %s\n", map->so_texture);
// 	printf("WE Texture: %s\n", map->we_texture);
// 	printf("EA Texture: %s\n", map->ea_texture);
// 	printf("Sprite Texture: %s\n", map->sprite_texture);
// 	printf("Floor Color: %d, %d, %d\n", map->floor_color[0], map->floor_color[1], map->floor_color[2]);
// 	printf("Ceiling Color: %d, %d, %d\n", map->ceiling_color[0], map->ceiling_color[1], map->ceiling_color[2]);
// 	printf("Map:\n");
// 	for (int i = 0; i < map->map_height; i++) {
// 		printf("%s", map->grid[i]);
// 	}
// }
