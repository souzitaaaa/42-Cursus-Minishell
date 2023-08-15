/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:02:18 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/15 17:26:39 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_n(t_main *main, t_type token, int *index, char *str)
{
	t_node	*new;
	char    **arr;

	(void)main;
	(void)index;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	arr = ft_split(str, 32);
	new->token.token = malloc(sizeof(char *) * ft_arrlen(arr) + 1);
	ft_arrlcpy(new->token.token, arr, ft_arrlen(arr) + 1);
	return (new);
}

int	add_token(t_main *main, t_type token, int *i, char *str)
{
	t_node	*new;

	new = create_n(main, token, i, str);
	if (!new)
		return (1);
	insert_last(&main->tokens, new);
	return (0);
}
