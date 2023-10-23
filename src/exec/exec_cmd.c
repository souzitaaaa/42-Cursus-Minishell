/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:04:20 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/23 12:54:15 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(char **command, t_main *main, bool child)
{
	if (ft_strcmp(command[0], "echo") == 0)
		echo(command, main, child);
	else if (ft_strcmp(command[0], "pwd") == 0)
		pwd(main, child);
	else if (ft_strcmp(command[0], "cd") == 0)
		check_cd(command, main, child);
	else if (ft_strcmp(command[0], "env") == 0)
		env(&main->env_list, main, child, command);
	else if (ft_strcmp(command[0], "export") == 0)
		export(main, command, child);
	else if (ft_strcmp(command[0], "unset") == 0)
		unset(main, command, child);
	else if (ft_strcmp(command[0], "exit") == 0)
		ft_exit(command, child, main, true);
   	else
       exec_other_cmd(command, main, child);
}

