/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:11:20 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/13 17:14:04 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool    not_special(int c)
{
    if (c != PIPE && c != IN && c != HEREDOC
        && c != OUT && c != APPEND)
        return true;
    return false;
}

void    search_extra_tokens(t_main *main, int *i)
{
	int start = *i;
	char    *str;

	while (main->input_prompt[*i] && not_special(main->input_prompt[*i]))
		(*i)++;
			printf("start %i i %i\n", start, *i);
	str = ft_substr(main->input_prompt, start, (*i - start));
			printf("string: %s\n", str);
	add_token(main, STRING, i);
	(*i)--;
}

void    search_tokens(t_main *main, int *i)
{
	printf("search tokens i %i\n", *i);
	if (main->input_prompt[*i] == PIPE)
		add_token(main, PIPE, i);
	else if (main->input_prompt[*i] == IN)
	{
		if (main->input_prompt[*i + 1] == OUT)
			add_token(main, HEREDOC, i);
		else
			add_token(main, IN, i);
	}
	else if (main->input_prompt[*i] == OUT)
	{
		if (main->input_prompt[*i + 1] == OUT)
			add_token(main, APPEND, i);
		else
			add_token(main, OUT, i);
	}
	//else if (main->input_prompt[*i] != " ") //tens de usar um strcmp, n complila
	//	search_extra_tokens(main, i);
}

void    print_tokens(t_list *tokens)
{
	int count = 0;
	t_node  *aux = tokens->head;

	printf("\033[1;32mPrinting tokens\033[0m\n");
	while (count++ < tokens->size)
	{
		printf("index: %i\n", aux->index);
		printf("type: %c\n", aux->type);
		aux = aux->next;
	}
}

void	lexer(t_main *main)
{
	int i;
	printf("\033[1;33m\t\tLexer function\033[0m\n");
	printf("Input: %s\n\n", main->input_prompt);
	init_list(main->tokens);
	i = 0;
	while(main->input_prompt[i])
	{
				printf("main i %i\n", i);
		search_tokens(main, &i);
		i++;
	}
	print_tokens(main->tokens);
}
