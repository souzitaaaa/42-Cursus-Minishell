/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:48:13 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/20 15:20:24 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void env(t_env *env, t_main *main, bool child, char **command)
{
	t_var	*current;
	
	if (command[1] != NULL)
	{
		if (child)
    		exit(127);
		set_exit_code(main, 127);
		return ;
	}
	current = env->head;
	env->i = 0;
	ft_printf("size env: %d\n", env->size);
	while (env->i++ < env->size)
	{
		ft_printf("%d: ", current->index);
		ft_printf("%s\n", current->var);
		current = current->next;
	}
	if (child)
        exit(0);
	set_exit_code(main, 0);
}
