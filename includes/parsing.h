/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:01:36 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 15:20:24 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "minirt.h"
#include "vector.h"

int valid_file(char *file);
void parse_file(const char *filename, t_scene_data *data);
void parse_line(char *line, t_scene_data *scene);
t_vec parse_vec(const char *str);

#endif
