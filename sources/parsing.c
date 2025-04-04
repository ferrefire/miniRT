/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:11:00 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 21:29:51 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "vector.h"
#include "scene.h"
#include "shapes.h"
#include "cleaning.h"
#include "libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	valid_file(char *file)
{
	char	*extension;
	int		path_len;
	int		ext_len;

	extension = ".rt";
	path_len = ft_strlen(file);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len
		|| !ft_strnstr(file + path_len - ext_len, extension, path_len))
		return (1);
	return (0);
}

void	parse_file(const char *filename, t_scene_data *data)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == '\0' || line[0] == '\n' || line[0] == '#')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		parse_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	parse_line(char *line, t_scene_data *scene)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return ;
	if (ft_strncmp(tokens[0], "A", ft_strlen("A") + 1) == 0)
		parse_ambient(tokens, scene);
	else if (ft_strncmp(tokens[0], "C", ft_strlen("C") + 1) == 0)
		parse_camera(tokens, scene);
	else if (ft_strncmp(tokens[0], "L", ft_strlen("L") + 1) == 0)
		parse_light(tokens, scene);
	else if (ft_strlen(tokens[0]) == 2)
		parse_shape(tokens, &scene->shapes);
	else
		printf("Error: Unknown Element Type = %s\n", tokens[0]);
	free_tokens(tokens);
}

t_vec	parse_vec(const char *str)
{
	t_vec	rgb;
	char	**tokens;
	int		i;

	tokens = ft_split(str, ',');
	i = 0;
	while (tokens && tokens[i])
		i++;
	if (i != 3)
	{
		printf("Error parsing rgb values");
		free_tokens(tokens);
		exit(EXIT_FAILURE);
	}
	rgb.x = atof(tokens[0]);
	rgb.y = atof(tokens[1]);
	rgb.z = atof(tokens[2]);
	free_tokens(tokens);
	return (rgb);
}
