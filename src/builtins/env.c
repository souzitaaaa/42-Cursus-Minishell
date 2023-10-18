/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:48:13 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/08 14:58:52 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*A env percorre a lista de variaveis de ambiente e imprime ela quando chamada, se a lista tiver vazia ou 
o env for chamado com argumentos dá erro*/
void	env(t_env *env, t_main *main, bool child, char **command)
{
	t_var	*current;

	if (env->size == 0)
	{
		if (main->flags.not_print == false)
			error_env(STDOUT_FILENO);
		exit_child(main, 127, child);
		return ;
	}
	if (command[1] != NULL)
	{
		if (main->flags.not_print == false)
			error_with_arg(STDOUT_FILENO, command[1]);
		exit_child(main, 127, child);
		return ;
	}
	current = env->head;
	env->i = 0;
	while (env->i++ < env->size)
	{
		ft_printf("%s\n", current->var);
		current = current->next;
	}
	exit_child(main, 0, child);
}
