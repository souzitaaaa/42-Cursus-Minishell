/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:38:26 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/18 04:11:29 by dinoguei         ###   ########.fr       */
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

void	init_main(t_main *main, char *input)
{
		main->input_prompt = input;
		init_list(&main->tokens, main);
		init_env(&main->env_list);
		main->env_arr = ft_calloc(sizeof(char *), 1);
		//main->stdout_copy = dup(1);
		init_ast(&main->input_exec);
		ini_quotes(&main->quotes);
}
