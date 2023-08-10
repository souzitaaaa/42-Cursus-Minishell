/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:11:20 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/10 17:01:33 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_array(t_main *main, int start, int end)
{
	char *str;

	str = malloc(sizeof(char) * (end - start + 1));
	str = ft_substr(main->input_prompt, start, end);
	printf("%s\n", str);
}

void	token_recognition(t_main *main)
{
	int i = 0;
	int j = 0;

	while (main->input_prompt[i])
	{
		j = i;
					printf("begin token: %i %c\n", j, main->input_prompt[j]);
		while (!ft_strchr("|<>", main->input_prompt[i])
			&& main->input_prompt[i + 1])
			i++;
					printf("end: %i %c\n\n", i, main->input_prompt[i]);
		put_array(main, j, i);
		i++;
	}
}


void	lexer(t_main *main)
{
	create_stack(&main->tokens);
	
	printf("\033[1;33m\t\tLexer function\033[0m\n");
	printf("Input: %s\n\n", main->input_prompt);

	token_recognition(main);
}
