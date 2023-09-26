/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_app.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 20:00:42 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/30 20:00:42 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	rdr_app(char **arr, t_main *main)
{
	int	fd;

	if(main->flags.rdr_err)
		return ;
	if(arr[1] == NULL)
	{
		fd = open(arr[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			rdr_error(arr[0], main, 0);
		dup2(fd, STDOUT_FILENO);
	}
	else
	{
		fd = open(arr[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			rdr_error(arr[1], main, 0);
		if(dup2(fd, ft_atoi(arr[0])) == -1)
		{
			if(dup2(fd, ft_atoi(arr[0])) == -1)
				rdr_error(arr[0], main, 1);
		}
	}
	close(fd);
}
