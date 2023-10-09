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

void create_new_node(t_main *main, int open_quote_type, int open_quote_position, int i)
{
    t_node_quotes *new_node;
    new_node = malloc(sizeof(t_node_quotes));
    if (!new_node)
        return ;
    new_node->type = open_quote_type;
    new_node->start = open_quote_position;
    new_node->end = i;
    insert_last_quotes(&main->quotes, new_node);
    printf("tamanho da lista --> %i\n", main->quotes.size);
}

int check_quotes(char c, int quotes)
{
	if (c == DQUOTE) {
		if (!quotes)
			return 1;
		else if (quotes == 1)
			return 0;
	} else if (c == SQUOTE) {
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
		if (c == SQUOTE || c == DQUOTE)
		{
			if ((quotes_analises == 1 || quotes_analises == 2) && open_quote_position == -1)
			{
				open_quote_position = i;
				open_quote_type = c;
			}
			else if (quotes_analises == 0 && open_quote_position != -1)
			{
				printf("Open quote of type %c at position %d, Close quote at position %d\n", open_quote_type, open_quote_position, i);
				create_new_node(main, open_quote_type, open_quote_position, i);
				// }
				// main->quotes.type = open_quote_type;
				// main->quotes.start = open_quote_position;
				// main->quotes.end = i;
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
        //!main->quotes.error = 1;
        return(0);
    }
    //print_quotes(&main->quotes);
    //printf("\033[1;35m\t\t[End quotes analises]\033[0m\n");
    return 0;
}

