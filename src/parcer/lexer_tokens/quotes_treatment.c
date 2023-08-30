/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_treatment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:18:03 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/25 16:18:03 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    quotes_treatment(t_main *main, int *i, char *str)
{
            printf("\033[1;32m\t\t(Quotes treatment)\033[0m\n");
        printf("Type: %c\n", (char)main->quotes.type);
        printf("Type: %i\n", main->quotes.start);
        printf("Type: %i\n", main->quotes.end);
        
            printf("\033[1;32m\t\t(End quotes treatment)\033[0m\n");
}