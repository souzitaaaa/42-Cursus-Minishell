/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:05:20 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/28 12:05:20 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_estatus(int pid, t_main *main)
{
	int	exit_status;

	waitpid(pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status) != 0)
		set_exit_code(main, WEXITSTATUS(exit_status));
	else
		set_exit_code(main, 0);
}

void	wait_set_line(int pid, t_main *main)
{
	int	exit_status;

	waitpid(pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status) != 0)
		main->line += WEXITSTATUS(exit_status);
}

void	error_fp(int pid, int exit_code, t_main *main)
{
	if (pid == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(exit_code), STDERR_FILENO);
		set_exit_code(main, exit_code);
		ft_exit(NULL, false, *main);
	}
}
