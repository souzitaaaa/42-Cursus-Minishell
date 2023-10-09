/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:22:13 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/04 11:22:13 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quotes_substr(t_quotes *quotes, char *str)
{
	int quotes_analises = 0;
	int i = 0;
	int open_quote_position = -1; // Posição da aspa de abertura
	char open_quote_type = '\0';  // Tipo da aspa de abertura
	//printf("\033[1;35m\t\t[Quotes analises]\033[0m\n");
	while (str[i] != '\0')
	{
		char c = str[i];
		quotes_analises = check_quotes(c, quotes_analises);
		if (c == SQUOTE || c == DQUOTE)
		{
			if ((quotes_analises == 1 || quotes_analises == 2) && open_quote_position == -1)
			{
				open_quote_position = i;
				open_quote_type = c;
			}
			else if (quotes_analises == 0 && open_quote_position != -1)
			{
				//printf("Open quote of type %c at position %d, Close quote at position %d\n", open_quote_type, open_quote_position, i);
				create_quotes_node(quotes, open_quote_type, open_quote_position, i);
				open_quote_position = -1; // Reset da posição da aspa de abertura
                open_quote_type = '\0';   // Reset do tipo da aspa de abertura
            }
        }
        //printf("Character: %c, index: %i ,quotes state: %d\n", c, i, quotes_analises);
        i++;
    }
	print_quotes(quotes);
}
