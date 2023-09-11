/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:49:31 by jede-ara          #+#    #+#             */
/*   Updated: 2023/09/11 16:34:15 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var *var_node(const char *var)
{
    t_var *new_node;

    new_node = (t_var *)malloc(sizeof(t_var));
    if (new_node == NULL)
    {
        //ft_error();
        exit(0);
    }
    new_node->var = ft_strdup(var);
    return (new_node);
}

void	add_var(t_env *env, t_var *var_new)
{
	static int	index = 0;

	if (env->head == NULL)
	{
		index = 0;
		env->head = var_new;
	    var_new->next = env->head;
	    var_new->prev = env->head;
	}
	else
	{
        index++;
		env->head->prev->next = var_new;
		var_new->prev = env->head->prev;
		var_new->next = env->head;
		env->head->prev = var_new;
	}
	var_new->index = index;
	env->size++;
}

void    set_env_list(t_main *main, char **envp)
{
    t_var   *aux;

    while (envp[main->env_list.i])
    {
        aux = var_node(envp[main->env_list.i]);
        add_var(&main->env_list, aux);
        main->env_list.i++;
    }
	unset(main, "OLDPWD", false);
}

void    print_var(t_env env)
{
    t_var   *current;

    env.i = 0;
    current = env.head;
    while (env.i++ < env.size)
    {
        printf("%s\n", current->var);
        current = current->next;
    }
}
