/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:00:15 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/21 16:00:15 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	add_token_quotes(t_main *main, t_type token, int *i, char *str, bool expand)
{
	t_node	*new;

	new = create_n_quotes(main, token, i, str, expand);
	if (!new)
		return (1);
	insert_last(&main->tokens, new);
	return (0);
}

int	add_token(t_main *main, t_type token, int *i, char *str)
{
	t_node	*new;

	new = create_n(main, token, i, str);
	if (!new)
		return (1);
	insert_last(&main->tokens, new);
	main->flags.free_flag.lexer_s = true;
	return (0);
}

int add_prev_token(t_main *main, int *i, char *str)
{
	t_node	*new;
	int j = 0;
				printf("\033[1;32m\t\t(Add_prev_token)\033[0m\n");
				printf("Adding str: %s\n", str);
	int index_wanted = main->tokens.size - 2;
				printf("index_wanted: %i\n", index_wanted);
	t_node  *token_insert = get_node_index(&main->tokens, index_wanted);
				print_arr(token_insert->token.arr);
				printf("token.arr size: %li\n", ft_arrlen(token_insert->token.arr));
	char    **temp = ft_calloc(ft_arrlen(token_insert->token.arr) + 2, sizeof(char *));
	int index = token_insert->index;
	ft_arrlcpy(temp, token_insert->token.arr, ft_arrlen(token_insert->token.arr) + 1);
	while (temp[j])
		j++;
	temp[j] = str;
	temp[j + 1] = NULL;
	new = create_n_prev(main, token_insert->token.type, temp);
	remove_node(&main->tokens, index);
	insert_node(&main->tokens, new, index);
				printf("\033[1;32m\t\t(End add_prev_token)\033[0m\n");
}
