/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:46:08 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/11 17:46:08 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	destroy_token(t_node *node)
{
	int	i;

	i = 0;
	while(node->token.arr[i] != NULL)
	{
		free(node->token.arr[i]);
		i++;
	}
	free(node->token.arr);
}

void	free_lexer(t_lexer *stack)
{
	t_node	*element;
	t_node	*temp;
	int		counter;

	if (stack->head == NULL)
		return ;
	element = stack->head;
	counter = 0;
	while (counter++ < stack->size)
	{
		destroy_token(element);
		temp = element;
		element = element->next;
		free(temp);
	}
	stack->head = NULL;
	stack->size = 0;
}

void    free_prompt(t_prompt *prompt_list)
{
    free(prompt_list->out);
    free(prompt_list->pwd);
    free(prompt_list->logname);
}

void    destroy(t_main *main)
{
    if (main->flags.free_flag.prompt_s == true)
        free_prompt(&main->prompt_list);
    if (main->flags.free_flag.lexer_s == true)
        free_lexer(&main->tokens);
}
