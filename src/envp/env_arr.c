/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:49:31 by jede-ara          #+#    #+#             */
/*   Updated: 2023/08/16 21:00:19 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_env_arr(t_main *main)
{
	t_var	*current;

	ft_free_array(&main->env_arr);
	main->env_arr = ft_calloc(sizeof(char *), main->env_list.size + 1);
	main->env_list.i = 0;
	current = main->env_list.head;
	while (main->env_list.i < main->env_list.size)
	{
		main->env_arr[main->env_list.i] = ft_strdup(current->var);
		//printf("%s\n", env->array[env->i]);
		main->env_list.i++;
		current = current->next;
	}
}