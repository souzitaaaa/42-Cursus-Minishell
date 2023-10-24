/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:59:13 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/30 14:59:13 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rdr_in(char **arr, t_main *main)
{
	int	fd;

	if (main->flags.rdr_err)
		return ;
	if (arr[1] == NULL)
	{
		fd = open(arr[0], O_RDONLY);
		if (fd == -1)
			rdr_error(arr[0], main, 0);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		fd = open(arr[1], O_RDONLY);
		if (fd == -1)
			rdr_error(arr[1], main, 0);
		else
		{
			if (dup2(fd, ft_atoi(arr[0])) == -1)
				rdr_error(arr[0], main, 1);
		}
	}
	close(fd);
}
