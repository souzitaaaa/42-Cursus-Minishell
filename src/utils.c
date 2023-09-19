/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:51:38 by joe               #+#    #+#             */
/*   Updated: 2023/08/28 18:33:45 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"

/**
 * Verifica o uso adequado de aspas duplas ("") e aspas simples ('') em um texto.
 *
 * @param c       O caractere atual sendo verificado.
 * @param quotes  O estado atual de citações (0 para nenhuma, 1 para aspas duplas, 2 para aspas simples).
 * @return        Retorna 1 se uma nova citação de aspas duplas começou,
 *                2 se uma nova citação de aspas simples começou,
 *                0 se uma citação de aspas foi fechada ou
 *                o valor atual de 'quotes' se nenhum estado de citação mudou.
 */
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
    int open_quote_position = -1; // Posição da aspa de abertura
    char open_quote_type = '\0';  // Tipo da aspa de abertura

    //printf("\033[1;35m\t\t[Quotes analises]\033[0m\n");
    while (main->input_prompt[i] != '\0')
    {
        char c = main->input_prompt[i];
        quotes_analises = check_quotes(c, quotes_analises);

        if (c == '\'' || c == '\"')
        {
            if ((quotes_analises == 1 || quotes_analises == 2) && open_quote_position == -1)
            {
                open_quote_position = i;
                open_quote_type = c;
            }
            else if (quotes_analises == 0 && open_quote_position != -1)
            {
                //printf("Open quote of type %c at position %d, Close quote at position %d\n", open_quote_type, open_quote_position, i);
                main->quotes.type = open_quote_type;
				main->quotes.start = open_quote_position;
				main->quotes.end = i;
				open_quote_position = -1; // Reset da posição da aspa de abertura
                open_quote_type = '\0';   // Reset do tipo da aspa de abertura
            }
        }

        //printf("Character: %c, index: %i ,quotes state: %d\n", c, i, quotes_analises);
        i++;
    }

    if (quotes_analises == 1 || quotes_analises == 2)
    {
        //printf("%s", SYNTAX_ERROR);
        error_quotes(STDERR_FILENO);
        set_exit_code(main, 2);
        main->quotes.error = 1;
        return(0);
    }
    //printf("\033[1;35m\t\t[End quotes analises]\033[0m\n");
    return 0;
}
