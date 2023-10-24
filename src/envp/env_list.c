/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:49:31 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/21 16:40:31 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var	*var_node(const char *var)
{
	t_var	*new_node;

	new_node = (t_var *)malloc(sizeof(t_var));
	if (new_node == NULL)
		exit(0);
	new_node->var = ft_strdup(var);
	return (new_node);
}

void	add_var(t_env *env, t_var *var_new, int index)
{
	if (env->head == NULL)
	{
		env->head = var_new;
		var_new->next = env->head;
		var_new->prev = env->head;
	}
	else
	{
		env->head->prev->next = var_new;
		var_new->prev = env->head->prev;
		var_new->next = env->head;
		env->head->prev = var_new;
	}
	if (index == -1)
		var_new->index = env->size;
	else
		var_new->index = index;
	env->size++;
}

void	set_env_list(t_main *main, char **envp)
{
	t_var	*aux;
	int		i;

	i = 0;
	while (envp[i])
	{
		aux = var_node(envp[i]);
		add_var(&main->env_list, aux, i);
		i++;
	}
	unset_env(main, "OLDPWD");
}

/*
void	print_var(t_env env)
{
	t_var	*current;

	env.i = 0;
	current = env.head;
    while (env.i++ < env.size)
    {
		printf("%d: ", current->index);
        printf("%s\n", current->var);
        current = current->next;
    }
}*/
