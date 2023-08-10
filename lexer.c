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

void	token_recognition(t_main *main)
{
	
}


void	lexer(t_main *main)
{
	create_stack(main->tokens);
	
	printf("\033[1;33m\t\tLexer function\033[0m\n");
	printf("Input: %s\n", main->input_prompt);
	token_recognition(main);
}
