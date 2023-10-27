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

void	rdr_in(char **arr, t_main *main, int rdr_fd)
{
	int	fd;

	if (check_errors(main, arr))
		return ;
	fd = open(arr[0], O_RDONLY);
	if (fd == -1)
		rdr_error(arr[0], main, 0);
	else if (rdr_fd == -666)
		dup2(fd, STDIN_FILENO);
	else
	{
		if (dup2(fd, rdr_fd) == -1)
			rdr_error(ft_itoa(rdr_fd), main, 1);
	}
	close(fd);
}
