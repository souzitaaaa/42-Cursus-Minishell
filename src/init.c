/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:38:26 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/14 17:01:11 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_list(t_list *stack)
{
	//stack->head = malloc(sizeof(t_node));

	stack->head = NULL;
	stack->size = 0;
}

void	init_ast(t_ast	*ast)
{
	ast->head = NULL;
	ast->counter = 0;
}
