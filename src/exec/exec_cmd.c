/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:04:20 by jede-ara          #+#    #+#             */
/*   Updated: 2023/08/18 03:51:25 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int init_builtins(char  *str)
{
    if (!str)
        return (0);
    if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "env") == 0 || ft_strcmp(str, "unset") == 0)
        return (1);
    return (0);
}

int	exec_cmd(char **command, t_main *main)
{
	int	exec;

	exec = 0;
	if (ft_strcmp(command[0], "echo") == 0)
		exec = echo(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		exec = pwd();
	/*else if (ft_strcmp(command[0], "cd") == 0)
		exec = ft_cd();*/
	else if (ft_strcmp(command[0], "env") == 0)
		exec = ft_env(&main->env_list); 
	/*else if (ft_strcmp(command[0], "export") == 0)
		exec = ft_export();*/
	else if (ft_strcmp(command[0], "unset") == 0)
		exec = ft_unset(main, command[1]);
	/*else if (ft_strcmp(command[0], "exit") == 0)
		exec = ft_exit();
   	else
       exec_other_cmd(command, main);*/
	return (exec);
}

void    test_exec(t_main *main)
{
    int count = 0;
	t_node  *aux = main->tokens.head;

	while (count++ < main->tokens.size)
	{
        exec_cmd(aux->token.arr, main);
		aux = aux->next;
	}
}
