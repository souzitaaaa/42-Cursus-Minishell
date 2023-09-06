/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:04:20 by jede-ara          #+#    #+#             */
/*   Updated: 2023/08/28 10:05:00 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int init_builtins(char  *str)
{
    if (!str)
        return (0);
    if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "env") == 0 || ft_strcmp(str, "export") == 0 ||ft_strcmp(str, "unset") == 0)
        return (1);
    return (0);
}

void	exec_cmd(char **command, t_main *main, bool child)
{
	if (ft_strcmp(command[0], "echo") == 0)
		echo(command, main, child);
	else if (ft_strcmp(command[0], "pwd") == 0)
		pwd(main, child);
	else if (ft_strcmp(command[0], "cd") == 0)
		cd(command[1], main, child);
	else if (ft_strcmp(command[0], "env") == 0)
		env(&main->env_list, main, child, command);
	else if (ft_strcmp(command[0], "export") == 0)
		export(main, command, child);
	else if (ft_strcmp(command[0], "unset") == 0)
		unset(main, command[1], child);
   	else
       exec_other_cmd(command, main, child);
}
