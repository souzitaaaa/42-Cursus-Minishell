/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:32:50 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/01 16:58:45 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*O parcer organiza o imput para a execução
//*1º caso a lista tenha apenas 1 elemento vai executar o comando, caso contrario segue para os passos seguintes
//*2º faz a analise sintatica e retorna caso a sintase esteja errada
//*3º verifica se existem pipes, nesse caso faz a arvore e depois a execuçao
//*4º caso nao hajam pipes, a execucao dos riderects é feita usando a lista

/*bool syntase()
{
	pipes seguidos, redirects seguidos, acabar em pipe ou riderect (o arr tem que ser NULL), começar em pipe, redirect e pipe por esta ordem, erro & (?)
}*/

//*Devolve verdadeiro se tiver pipes ou rdr e falso se nao tiver
/*bool	find_tk(t_lexer tokens)
{
	int counter;
	t_node *aux;

	counter = 0;
	aux = tokens.head;
	while(counter++ < tokens.size)
	{
		if(aux->token.type != STRING)
			return (true);
		aux = aux->next;
	}
	return (false);
}*/

bool	find_pipes(t_lexer tokens)
{
	int counter;
	t_node *aux;

	counter = 0;
	aux = tokens.head;
	while(counter++ < tokens.size)
	{
		if(aux->token.type == PIPE)
			return (true);
		aux = aux->next;
	}
	return (false);
}

void	parcer(t_main *main)
{
	//if(!syntase())
		//	return ;
	if(main->tokens.size == 1 && main->tokens.head->token.type == STRING)
		exec_cmd(main->tokens.head->token.arr, main, false);
	//concatenar os comandos
	else
	{
		if(find_pipes(main->tokens))
		{
			test_ast(main->tokens, &main->ast);
			init_exec_ast(main->ast, main);
		}
		else
		{
			printf("entra aqui\n");
			init_rdr(main->tokens, main);
		}
	}
}
