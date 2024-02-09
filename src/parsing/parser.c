/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 22:45:15 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/02/09 23:25:16 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/parser.h>

int parse_resolution(char *line, t_map *map) 
{
    return sscanf(line, "R %d %d", &map->resolution_x, &map->resolution_y);
}

int parse_texture(char *line, char **texture) {
    *texture = strdup(line + 3);
    if (!*texture) {
        perror("Error: Memory allocation failed");
        return 0;
    }
    return 1;
}

int parse_color(char *line, int color[3]) {
    return sscanf(line, "F %d,%d,%d", &color[0], &color[1], &color[2]);
}

int parse_map(char *line, t_map *map, int *map_lines) {
    int len = strlen(line);
    map->grid[*map_lines] = malloc(len + 1);
    if (!map->grid[*map_lines]) {
        perror("Error: Memory allocation failed");
        return 0;
    }
    strcpy(map->grid[*map_lines], line);
    (*map_lines)++;
    return 1;
}

int parse_config(char *filename, t_map *map) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error: Could not open file");
        return 0;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int map_lines = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        if (line[0] == 'R') {
            if (!parse_resolution(line, map)) {
                fclose(file);
                free(line);
                return 0;
            }
        } else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E') {
            char **texture = NULL;
            if (line[0] == 'N') texture = &map->no_texture;
            else if (line[0] == 'S') texture = &map->so_texture;
            else if (line[0] == 'W') texture = &map->we_texture;
            else if (line[0] == 'E') texture = &map->ea_texture;

            if (!parse_texture(line, texture)) {
                fclose(file);
                free(line);
                return 0;
            }
        } else if (line[0] == 'S') {
            if (!parse_texture(line, &map->sprite_texture)) {
                fclose(file);
                free(line);
                return 0;
            }
        } else if (line[0] == 'F') {
            if (!parse_color(line, map->floor_color)) {
                fclose(file);
                free(line);
                return 0;
            }
        } else if (line[0] == 'C') {
            if (!parse_color(line, map->ceiling_color)) {
                fclose(file);
                free(line);
                return 0;
            }
        } else if (line[0] == '1' || line[0] == '0') {
            if (!parse_map(line, map, &map_lines)) {
                fclose(file);
                free(line);
                return 0;
            }
        }
    }

    fclose(file);
    free(line);

    map->map_width = map_lines > 0 ? strlen(map->grid[0]) : 0;
    map->map_height = map_lines;

    return 1;
}

void print_config(t_map *map) {
    printf("Resolution: %dx%d\n", map->resolution_x, map->resolution_y);
    printf("NO Texture: %s\n", map->no_texture);
    printf("SO Texture: %s\n", map->so_texture);
    printf("WE Texture: %s\n", map->we_texture);
    printf("EA Texture: %s\n", map->ea_texture);
    printf("Sprite Texture: %s\n", map->sprite_texture);
    printf("Floor Color: %d, %d, %d\n", map->floor_color[0], map->floor_color[1], map->floor_color[2]);
    printf("Ceiling Color: %d, %d, %d\n", map->ceiling_color[0], map->ceiling_color[1], map->ceiling_color[2]);

    printf("Map:\n");
    for (int i = 0; i < map->map_height; i++) {
        printf("%s", map->grid[i]);
    }
}
