/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:38:26 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/19 16:15:53 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"


void	ini_quotes(t_quotes *quotes)
{
	quotes->error = 0;
}

void	init_ast(t_ast	*ast)
{
	ast->head = NULL;
	ast->counter = 0;
}

void	init_list(t_lexer *stack, t_main *main)
{
	stack->head = NULL;
	stack->size = 0;
	stack->str_len = ft_strlen(main->input_prompt);
}

void	init_env(t_env *stack)
{
	stack->head = NULL;
	stack->size = 0;
	stack->i = 0;
}
void	init_std(t_std *fd)
{
	fd->stdin = dup(0);
	fd->stdout = dup(1);
	fd->stderr = dup(2);
}
//* Inicia as variaveis da estrutura principal (t_main) que têm que ser iniciadas sempre que se inicia o prompt
// Ou seja, as estruturas relacionadas com o imput
//! Dar free sempre que se inicia novamente
void	init_input(t_main *main, char *input)
{
		main->input_prompt = input;
		init_list(&main->tokens, main);
		ini_quotes(&main->quotes);
		init_ast(&main->input_exec);
		init_std(&main->fd); //!duvida se é aqui ou no init main
}

//* Inicia as variaveis da estrutura principal (t_main) que têm que ser iniciadas apenas uma vez
void	init_main(t_main *main, char **envp)
{
		init_env(&main->env_list);
		set_env_list(main, envp);
		main->env_arr = ft_calloc(sizeof(char *), 1);
		main->exit_code = 0;
}
