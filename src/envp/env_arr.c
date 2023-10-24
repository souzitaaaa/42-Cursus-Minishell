/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:49:31 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/24 11:26:34 by rimarque         ###   ########.fr       */
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
		main->env_list.i++;
		current = current->next;
	}
}
