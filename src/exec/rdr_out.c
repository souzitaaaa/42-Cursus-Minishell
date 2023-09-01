/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:56:07 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/30 19:56:07 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rdr_out(char **arr, t_main *main)
{
	int	fd;

	if(main->flags.rdr_err)
		return ;
	if(arr[1] == NULL)
	{
		printf("arr[0]: %d\n", arr[0][3]);
		fd = open(arr[0], O_WRONLY | O_CREAT | O_TRUNC, 0644); //!	error_management(file, 0, 0);
		/*if (fd == -1)
		{
			close(fd);
			printf("error\n");
			exit(errno);
		}*/
		printf("fd: %d\n", fd);
		printf("stdout: %d\n", STDOUT_FILENO);
		//ft_printf("dup2 result: %d\n", dup2(fd, STDOUT_FILENO));
		printf("fd: %d\n", fd);
		printf("stdout: %d\n", STDOUT_FILENO);
	//	close(fd);
		/*if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			ft_printf("pipex: %s\n", strerror(errno));
			//write(main->fd.stdout, "erro\n", 5);
			exit(errno);
		}*/
	}
	else
	{
		fd = open(arr[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//!if (fd == -1)
		//!	error_management(file, 0, 0);
		if(dup2(fd, ft_atoi(arr[0])) == -1)
		{
			 //!ERROR HANDLING "bad file descriptor" set exit code
			//! set_rdr_err(main); //parar os rdr exceto o here doc
		}
	}
	ft_printf("entra aqui 5\n");
	close(fd);
}
