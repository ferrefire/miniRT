/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:24:26 by ferre         #+#    #+#                 */
/*   Updated: 2025/02/19 18:28:31 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "initiation.h"
#include "cleaning.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	t_data *data;

	printf("start\n");
	data = initiateData();
	cleanData(data);
	printf("end\n");
	exit(EXIT_SUCCESS);
}