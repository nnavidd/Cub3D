/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnabaeei <nnabaeei@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:16:02 by nnabaeei          #+#    #+#             */
/*   Updated: 2024/01/15 16:56:59 by nnabaeei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/cub_3d.h>

// Exit the program as failure.
static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void	ft_hook(void *param)
{
	const mlx_t	*mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void	initiate_map_variable(t_map *map)
{
	map->resolution_x = 0;
	map->resolution_y = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->ea_texture = NULL;
	map->we_texture = NULL;
	map->floor_color[0] = 0;
	map->ceiling_color[0] = 0;
	map->map = NULL;
	map->map_width = 0;
	map->map_height = 10;
}

int	main(void)
{
	t_map	*map_details;

	map_details = malloc(sizeof(t_map));
	initiate_map_variable(map_details);

	if (map_details->map_height == 10)
	{
		printf("hi\n");
		exit(1);
	}
	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}