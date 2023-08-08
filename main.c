/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:29:18 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/08 19:12:57 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prompt(void)
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
		printf("Comando inserido: %s\n", input);
		free(input);
	}
}

void	signaltreatment(void)
{
	struct sigaction	sig;
	
	sig.sa_sigaction = 
	sig.sa_flags = SA_SIGINFO;
	
}

int	main(void)
{
	signaltreatment();
	init_prompt();
}
