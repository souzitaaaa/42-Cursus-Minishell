/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:02:18 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/14 17:02:31 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_n(t_main *main, t_type token, int *i)
{
	t_node	*new;

	(void)main;
	(void)i;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	//new->token = main->input_prompt[i];
	return (new);
}

int	add_token(t_main *main, t_type token, int *i)
{
	t_node	*new;

	new = create_n(main, token, i);
	if (!new)
		return (1);
	insert_last(&main->tokens, new);
	return (0);
}
