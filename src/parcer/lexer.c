/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:11:20 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/15 12:46:50 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool    special_chr(char c)
{
	printf("Comparing %c\n", c);
    if (ft_strchr("|<>", c))
    {
        printf("Encontrou limite\n");
        return true;
    }
    return false;
}

void    search_extra_tokens(t_main *main, int *i)
{
	int start = *i;
	char    *str;
	bool    run = true;

	while (*i <= main->tokens.str_len && run && main->input_prompt[*i])
	{
		if (special_chr(main->input_prompt[*i]) == false)
            (*i)++;
        else
            run = false;
	}
				printf("start %i i(end) %i\n", start, *i);
	str = ft_substr(main->input_prompt, start, (*i - start));
				printf("string: %s\n", str);
	add_token(main, STRING, i);
	(*i)--;
}

void search_tokens(t_main *main, int *i)
{
                printf("search tokens i %i\n", *i);
    if (*i <= main->tokens.str_len && main->input_prompt[*i] == PIPE)
    {
        printf("Token %c = %i found!\n", PIPE, PIPE);
        add_token(main, PIPE, i);
    }
    else if (*i <= main->tokens.str_len && main->input_prompt[*i] == IN)
    {
        if (*i + 1 <= main->tokens.str_len && main->input_prompt[*i + 1] == IN)
        {
            printf("Token %c = %i found!\n", HEREDOC, HEREDOC);
            add_token(main, HEREDOC, i);
            (*i)++;
        }
        else
        {
            printf("Token %c = %i found!\n", IN, IN);
            add_token(main, IN, i);
        }
    }
    else if (*i <= main->tokens.str_len && main->input_prompt[*i] == OUT)
    {
        if (*i + 1 <= main->tokens.str_len && main->input_prompt[*i + 1] == OUT)
        {
            printf("Token %c = %i found!\n", APPEND, APPEND);
            add_token(main, APPEND, i);
            (*i)++;
        }
        else
        {
            printf("Token %c = %i found!\n", OUT, OUT);
            add_token(main, OUT, i);
        }
    }
    else if (*i <= main->tokens.str_len && main->input_prompt[*i] != ' ')
        search_extra_tokens(main, i);
}

void    print_tokens(t_list *tokens)
{
	int count = 0;
	t_node  *aux = tokens->head;

				printf("\033[1;32mPrinting tokens\033[0m\n");
	while (count++ < tokens->size)
	{
		printf("index: %i\n", aux->index);
		printf("type: %c\n", aux->token.type);
		aux = aux->next;
	}
}

void	lexer(t_main *main)
{
	int i;
				printf("\033[1;33m\t\t[Lexer function]\033[0m\n");
	init_list(&main->tokens, main);
				printf("Input: %s Size: %i\n\n", main->input_prompt, main->tokens.str_len);
	i = 0;
	while(main->input_prompt[i] && i <= main->tokens.str_len)
	{
				printf("main i %i\n", i);
		search_tokens(main, &i);
		i++;
	}
	print_tokens(&main->tokens);
}
