/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:38:26 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/14 18:20:52 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_list(t_list *stack)
{
	stack->head = NULL;
	stack->size = 0;
}

void	init_env(t_env *stack)
{
	stack->head = NULL;
	stack->size = 0;
	stack->i = 0;
}

void	init_ast(t_ast	*ast)
{
	ast->head = NULL;
	ast->counter = 0;
}
