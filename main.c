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

#include "minishell.h"

//TODO:

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
		main->input_prompt = input;
		//printf("Comando inserido: %s\n", main->input_prompt);
		lexer(main);
		add_history(input);
		free(input);
	}
}

int	main(void)
{
	t_main	main;

	init_prompt(&main);
}
