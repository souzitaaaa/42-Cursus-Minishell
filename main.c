/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ai <jede-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:29:18 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/10 16:09:15 by jede-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_prompt(t_main	*main)
{
	char		*input;
	const char	*prompt;

	prompt = "\033[1;31mminihell😈--> \033[1;0m";
	while (1)
	{
		input = readline(prompt);
		if (input == NULL)
			break;
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		add_history(input);
		main->input_prompt = input;
		list_var(main);
		print_var(main->env);
		lexer(main);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_main	main;
	
	main.envp = envp;
	(void)argc;
	(void)argv;
	init_prompt(&main);
	//tratar aspas
	//lexer
	//se nao tiver carecteres expeciais vai logo para a exec_cmd;
	//analise sintatica --> se for falso da ERRO
	//AST
	//init_exec
}
