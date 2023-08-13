/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:02:18 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/13 17:14:08 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_n(t_main *main, t_type token, int *i)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = token;
	//new->token = main->input_prompt[i];
	return (new);
}

int	add_token(t_main *main, t_type token, int *i)
{
	t_node	*new;

	new = create_n(main, token, i);
	if (!new)
		return (1);
	insert_last(main->tokens, new);
	return (0);
}
