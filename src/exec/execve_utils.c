/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:46:02 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/19 16:13:43 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//COPIA DO PIPEX

void	free_pathname(char	*pathname, int flag)
{
	if (flag == 1)
		ft_free_str(&pathname);
}
//!como escrever para o stderr, usar o putstr?
void	error_management(char *str, t_main *main)
{
	/*if (!str)
	{
		ft_printf("pipex: %s\n", strerror(errno));
		exit(exit_code);
	}
	if (stderr == 0)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), str);
		exit(exit_code);
	}*/
	if (ft_strncmp("/", str, 1)) //cmd normal
		error_msg_cmd(str, main->fd.stderr);
	else if (!ft_strncmp(".sh", str + ft_strlen(str) - 3, 3)) //se acabar em .sh //flag
		error_msg_cmd(str, main->fd.stderr);
	else //se começar por "/"" (ou seja se der o caminho)
		error_msg_file(str, main->fd.stderr);
	exit(127);
}
