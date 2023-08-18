/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 21:46:02 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/18 03:50:52 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//COPIA DO PIPEX

void	free_pathname(char	*pathname, int flag)
{
	if (flag == 1)
		ft_free_str(&pathname);
}

void	error_management(char *str, int stdout_copy, int exit_code)
{
	if (!str)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno));
		exit(exit_code);
	}
	if (stdout_copy == 0)
	{
		ft_printf("pipex: %s: %s\n", strerror(errno), str);
		exit(exit_code);
	}
	dup2(stdout_copy, STDOUT_FILENO);
	if (ft_strncmp("/", str, 1))
		ft_printf("pipex: Command not found: %s\n", str);
	else if (!ft_strncmp(".sh", str + ft_strlen(str) - 3, 3))
		ft_printf("pipex: Command not found: %s\n", str);
	else
		ft_printf ("pipex: %s: %s\n", strerror(errno), str);
}
