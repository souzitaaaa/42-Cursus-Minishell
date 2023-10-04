/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:06:55 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/21 16:06:55 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_n(t_main *main, t_type token, int *i, char *str)
{
	t_node	*new;
	char	**arr;

	(void)main;
	(void)index;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	//meter aqui o tratamento de quotes
	arr = ft_split(str, 32);
	check_expansion(main, arr);
	new->token.arr = ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
	ft_arrlcpy(new->token.arr, arr, ft_arrlen(arr) + 1);
	new->token.quotes = false;
	return (new);
}

t_node	*create_n_prev(t_main *main, t_type token, char **arr)
{
	t_node	*new;

	(void)main;
	(void)index;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	check_expansion(main, arr);
	new->token.arr = ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
	ft_arrlcpy(new->token.arr, arr, ft_arrlen(arr) + 1);
	new->token.quotes = false;
	//! falta o free da arr
	return (new);
}

t_node	*create_n_quotes(t_main *main, t_type token, int *i, char **result, bool expand)
{
	t_node	*new;

	(void)main;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	new->token.arr = ft_calloc(ft_arrlen(result) + 1, sizeof(char *));
	ft_arrlcpy(new->token.arr, result, ft_arrlen(result) + 1);
	new->token.quotes = false;
	//! falta o free da arr
	return (new);
}
