/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:11:00 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 14:18:45 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

#include <stdlib.h> // For malloc, free, exit
#include <unistd.h> // For open, close, read, write
#include <fcntl.h>	// For file opening flags

void valid_file(char *file)
{
	char *extension;
	int path_len;
	int ext_len;

	extension = ".rt";
	path_len = ft_strlen(file);
	ext_len = ft_strlen(extension);
	if (path_len < ext_len || !ft_strnstr(file + path_len - ext_len, extension, path_len))
	{
		printf("Error\nThe file does have the '.rt' extension.\n");
		exit(1);
	}
}

void parse_file(const char *filename, t_data *data)
{
	int fd;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == '\0' || line[0] == '\n' || line[0] == '#')
		{
			free(line);
			continue;
		}
		parse_line(line, &data->scene_data);
		free(line);
	}
	close(fd);
}

void parse_line(char *line, t_scene_data *scene)
{
	char **tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		// free_tokens(tokens);
		return;
	}
	if (ft_strncmp(tokens[0], "A", ft_strlen("A") + 1) == 0)
		parse_ambient(tokens, scene);
	else if (ft_strncmp(tokens[0], "C", ft_strlen("C") + 1) == 0)
		parse_camera(tokens, scene);
	else if (ft_strncmp(tokens[0], "L", ft_strlen("L") + 1) == 0)
		parse_light(tokens, scene);
	else if (ft_strlen(tokens[0]) == 2)
		parse_shape(tokens, scene);
	else
		printf("Error: Unknown Element Type = %s\n", tokens[0]);
	free_tokens(tokens);
}