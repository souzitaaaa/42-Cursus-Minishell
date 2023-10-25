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

/*A env percorre a lista de variaveis de ambiente e imprime ela quando chamada,
se a lista tiver vazia ou o env for chamado com argumentos dá erro*/
void	print_env(t_env	*env)
{
	t_var	*current;
	
	current = env->head;
	env->i = 0;
	while (env->i++ < env->size)
	{
		ft_printf("%s\n", current->var);
		current = current->next;
	}
}

void	env(t_env *env, t_main *main, bool child, char **command)
{
	char	*path;

	path = get_envvar("PATH", env);
	if (path == NULL)
	{
		error_msg_file("env", STDERR_FILENO, FILE_ERROR);
		return ;
	}
	ft_free_str(&path);
	if (env->size == 0)
	{
		if (main->flags.not_print == false)
			error_msg_file("env", STDERR_FILENO, FILE_ERROR);
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
	print_env(env);
	exit_child(main, 0, child);
}
