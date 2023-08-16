/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:04:20 by jede-ara          #+#    #+#             */
/*   Updated: 2023/08/16 17:31:42 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int init_builtins(char  *str)
{
    if (!str)
        return (0);
    if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "pwd") == 0)
        return (1);
    return (0);
}

int	builtins(char **command)
{
	int	exec;

	exec = 0;
	if (ft_strcmp(command[0], "echo") == 0)
		exec = echo(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		exec = pwd();
	/*else if (ft_strcmp(command[0], "cd") == 0)
		exec = ft_cd();
	else if (ft_strcmp(command[0], "env") == 0)
		exec = ft_env();
	else if (ft_strcmp(command[0], "export") == 0)
		exec = ft_export();
	else if (ft_strcmp(command[0], "unset") == 0)
		exec = ft_unset();
	else if (ft_strcmp(command[0], "exit") == 0)
		exec = ft_exit();
    else 
        vai pro caralho*/
	return (exec);
}

void    merda(t_main *main)
{
    int count = 0;
	t_node  *aux = main->tokens.head;

	while (count++ < main->tokens.size)
	{
        builtins(aux->token.token);
		aux = aux->next;
	}
}