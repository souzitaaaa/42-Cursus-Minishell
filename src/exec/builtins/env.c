/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:48:13 by jede-ara          #+#    #+#             */
/*   Updated: 2023/08/18 03:46:21 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_env(t_env *env)
{
	t_var	*current;
	
	current = env->head;
	env->i = 0;
	while (env->i++ < env->size)
	{
		ft_printf("%s\n", current->var);
		current = current->next;
	}
	return (0);
}