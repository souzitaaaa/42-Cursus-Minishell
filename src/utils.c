/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:51:38 by joe               #+#    #+#             */
/*   Updated: 2023/08/18 03:57:40 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Verifica o uso adequado de aspas duplas ("") e aspas simples ('') em um texto.
 *
 * @param c       O caractere atual sendo verificado.
 * @param quotes  O estado atual de citações (0 para nenhuma, 1 para aspas duplas, 2 para aspas simples).
 * @return        Retorna 1 se uma nova citação de aspas duplas começou,
 *                2 se uma nova citação de aspas simples começou,
 *                0 se uma citação de aspas foi fechada ou
 *                o valor atual de 'quotes' se nenhum estado de citação mudou.
 */

#include "../includes/minishell.h"
#include "../includes/structs.h"

int check_quotes(char c, int quotes) 
{
	if (c == '\"') {
		if (!quotes)
			return 1;
		else if (quotes == 1)
			return 0;
	} else if (c == '\'') {
		if (!quotes)
			return 2;
		else if (quotes == 2)
			return 0;
	}
	return quotes;
}

int check_quotes_print(t_main *main)
{
	int quotes_analises = 0;
	int i = 0;

	printf("\033[1;35m\t\t[Quotes analises]\033[0m\n");
	while (main->input_prompt[i] != '\0') 
	{
		char c = main->input_prompt[i];
		quotes_analises = check_quotes(c, quotes_analises);
		printf("Character: %c, Quotes state: %d\n", c, quotes_analises);
		i++;
	}
	
	if (quotes_analises == 1 || quotes_analises == 2)
	{
		//printf("%s", SYNTAX_ERROR);
		main->quotes.error = 1;
	}
	   		
	printf("\n");
	
	return(0);
}

