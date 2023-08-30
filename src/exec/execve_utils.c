/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:46:02 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/25 12:54:02 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pathname(char	*pathname, int flag)
{
	if (flag == 1)
		ft_free_str(&pathname);
}

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
	if (ft_strncmp("/", str, 1) && ft_strncmp("./", str, 2)) //cmd normal
		error_msg_cmd(str, main->fd.stderr);
	else 													//se começar por "/"" (ou seja se der o caminho)
		error_msg_file(str, main->fd.stderr);
	exit(127);
}
