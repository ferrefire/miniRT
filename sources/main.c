/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:24:26 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 15:26:08 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "initiation.h"
#include "cleaning.h"
#include "rendering.h"
#include "input.h"
#include "vector.h"
#include "utilities.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	t_data *data;

	
  if (argc != 2 || valid_file(argv[1]) == 1)
  {
    printf("Error: Could not Open file or no file given as input.\n");
    return (1);
  }

  printf("start\n");

  data = initiateData();
  parse_file(argv[1], &data->scene_data);
	setHooks(data);

	renderImage(data);
	//printf("sphere cound: %i\n", data->scene_data.shapes.sphereCount);

	cleanData(data);
	printf("end\n");
	exit(EXIT_SUCCESS);
}
