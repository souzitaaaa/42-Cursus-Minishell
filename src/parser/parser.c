/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:32:50 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/13 18:20:52 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_ex_status;
//*O parcer organiza o imput para a execução
//*1º faz a analise sintatica e retorna caso a sintase esteja errada
//*2º caso a lista tenha apenas 1 elemento tipo STRING vai executar o comando, caso contrario segue para os passos seguintes
//*3º concatena todos os tipos strings no mesmo comando, até ao próximo pipe
//*4º verifica se existem pipes, nesse caso faz a arvore e depois a execuçao
//*5º caso nao hajam pipes, a execucao dos riderects é feita usando a lista

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

void	parser(t_main *main)
{
	if(main->tokens.size == 0)
		return ;
	if(!syntax_analysis(main->tokens))
	{
		set_exit_code(main, 2);
		return ;
	}
	if(main->tokens.size == 1 && main->tokens.head->token.type == STRING)
	{
		exec_cmd(main->tokens.head->token.arr, main, false);
		return ;
	}
	cmdcat(&main->tokens);
	//print_tokens(&main->tokens);
	if(find_pipes(main->tokens))
	{
		create_ast(main->tokens,&main->ast);
		//print_ast(*ast);
		exec_hd_p(&main->ast, main);
		if(g_ex_status == 130)
			return ;
		pipex(&main->ast, main);
	}
	else
		init_rdr(main->tokens, main);
}
