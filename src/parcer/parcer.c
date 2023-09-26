/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:32:50 by rimarque          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/12 20:17:06 by jenny            ###   ########.fr       */
=======
/*   Updated: 2023/09/23 20:30:16 by rimarque         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*O parcer organiza o imput para a execução
//*1º faz a analise sintatica e retorna caso a sintase esteja errada
//*2º caso a lista tenha apenas 1 elemento tipo STRING vai executar o comando, caso contrario segue para os passos seguintes
//*3º concatena todos os tipos strings no mesmo comando, até ao próximo pipe
//*4º verifica se existem pipes, nesse caso faz a arvore e depois a execuçao
//*5º caso nao hajam pipes, a execucao dos riderects é feita usando a lista

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
	if(main->tokens.size == 0)
		return ;
	if(main->tokens.size == 1 && main->tokens.head->token.type == STRING)
	{
		exec_cmd(main->tokens.head->token.arr, main, false);
		return ;
	}
	cmdcat(&main->tokens);
	print_tokens(&main->tokens);
	if(find_pipes(main->tokens))
	{
		test_ast(main->tokens, &main->ast);
		pipex(&main->ast, main);
	}
	else
		init_rdr(main->tokens, main);
}
