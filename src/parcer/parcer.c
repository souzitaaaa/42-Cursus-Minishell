/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:32:50 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/28 10:02:06 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*O parcer organiza o imput para a execução
//*1º caso a lista tenha apenas 1 elemento vai executar o comando, caso contrario segue para os passos seguintes
//*2º faz a analise sintatica e retorna caso a sintase esteja errada
//*3º verifica se existem pipes, nesse caso faz a arvore e depois a execuçao
//*4º caso nao hajam pipes, a execucao dos riderects é feita com a a lista

/*bool syntase()
{
	pipes seguidos, redirects seguidos, acabar em pipe ou riderect...
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
	if(main->tokens.size == 1)
		exec_cmd(main->tokens.head->token.arr, main, false);
	else
	{
		//if(!syntase())
		//	return ;
		if(find_pipes(main->tokens))
		{
			test_ast(main->tokens, &main->ast);
			init_pipe(main->ast, main);
		}
		//else
		//	init_rdr(main->tokens, main);
	}
}
