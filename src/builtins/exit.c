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

void	ft_exit(char **command, bool child, t_main main)
{
	int exit_code;

	//!clear history
	//free_all(); //!É PARA DAR FREE AQUI
	if (!child)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!command)
		exit(main.exit_code);
	if (!command[1])
		exit(main.exit_code);
	if (ft_isnbr(command[1]) && command[2] == NULL)
	{
		exit_code = ft_atoi(command[1]);
		exit((unsigned char)exit_code);
	}
	if (ft_isnbr(command[1]) && command[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		exit(1);
	}
	if (!ft_isnbr(command[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(command[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(2);
	}
}
