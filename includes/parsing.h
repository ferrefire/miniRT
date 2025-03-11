/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:01:36 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 14:18:06 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "minirt.h"

void valid_file(char *file);
void parse_file(const char *filename, t_data *data);
void parse_line(char *line, t_scene_data *scene);

#endif