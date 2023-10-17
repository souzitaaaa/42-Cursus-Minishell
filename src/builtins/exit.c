/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:19:35 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/12 16:19:35 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit(t_main *main, int exit_code)
{
	destroy_main(main);
	exit(exit_code);
}

void	ft_exit(char **command, bool child, t_main *main)
{
	int exit_code;

	rl_clear_history();
	if (!child)
		ft_putendl_fd("exit", STDERR_FILENO);
	if(!command)
		free_and_exit(main, main->exit_code);
	if(!command[1])
		free_and_exit(main, main->exit_code);
	if(ft_isnbr(command[1]) && command[2] == NULL)
	{
		exit_code = ft_atoi(command[1]);
		free_and_exit(main, (unsigned char)exit_code);
	}
	if(ft_isnbr(command[1]) && command[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		free_and_exit(main, 1);
	}
	if(!ft_isnbr(command[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(command[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		free_and_exit(main, 2);
	}
}

void	exit_child(t_main *main, int exit_code, bool child)
{
	set_exit_code(main, exit_code);
	if (child)
		ft_exit(NULL, true, main);
}
