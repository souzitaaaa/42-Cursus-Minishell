/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:11:20 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/16 14:49:12 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//* Cerebro da separacao de tokens, vai ver oque tem a string nesse index
	//* e posteriormente tratar de mandar, tudo tratado para a lista
void search_tokens(t_main *main, int *i)
{
				//printf("search tokens i %i\n", *i);
	if (*i <= main->tokens.str_len && main->input_prompt[*i] == PIPE)
	{
		//printf("Token %c = %i found!\n", PIPE, PIPE);
		add_token(main, PIPE, i, "|");
	}
	else if (*i <= main->tokens.str_len && main->input_prompt[*i] == IN)
	{
		if (*i + 1 <= main->tokens.str_len && main->input_prompt[*i + 1] == IN)
		{
			//printf("Token %c = %i found!\n", HEREDOC, HEREDOC);
			add_token(main, HEREDOC, i, "<<");
			(*i)++;
		}
		else
		{
			//printf("Token %c = %i found!\n", IN, IN);
			add_token(main, IN, i, "<");
		}
	}
	else if (*i <= main->tokens.str_len && main->input_prompt[*i] == OUT)
	{
		if (*i + 1 <= main->tokens.str_len && main->input_prompt[*i + 1] == OUT)
		{
			//printf("Token %c = %i found!\n", APPEND, APPEND);
			add_token(main, APPEND, i, ">>");
			(*i)++;
		}
		else
		{
			//printf("Token %c = %i found!\n", OUT, OUT);
			add_token(main, OUT, i, ">");
		}
	}
	else if (*i <= main->tokens.str_len && main->input_prompt[*i] != ' ')
		search_extra_tokens(main, i);
}

//* Funcao para debug, podem reutiliza-la, so mandar a lista que pretender
	//* e os argumentos que querem imprimir
void    print_tokens(t_list *tokens)
{
	int count = 0;
	t_node  *aux = tokens->head;

				printf("\033[1;32m\tPrinting tokens\033[0m\n");
	while (count++ < tokens->size)
	{
		printf("\033[1;34mindex:\033[0m %i\n", aux->index);
		printf("\033[1;34mtype:\033[0m %c\n", aux->token.type);
		printf("\033[1;34marr:\033[0m \n");
		print_arr(aux->token.token);
		aux = aux->next;
	}
}

//* Funcao main do lexer, vai simplesmente iniciar a lista e
	//* percorrer a str de input para fazer a divisao de tokens
void	lexer(t_main *main)
{
	int i;
				printf("\033[1;33m\t\t[Lexer function]\033[0m\n");
	init_list(&main->tokens, main);
				printf("Input: %s Size: %i\n\n", main->input_prompt, main->tokens.str_len);
	i = 0;
	while(main->input_prompt[i] && i <= main->tokens.str_len)
	{
				//printf("main i %i\n", i);
		search_tokens(main, &i);
		i++;
	}
	print_tokens(&main->tokens);
}
