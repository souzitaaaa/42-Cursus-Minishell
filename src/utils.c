/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:51:38 by joe               #+#    #+#             */
/*   Updated: 2023/08/16 16:10:36 by joe              ###   ########.fr       */
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

// int check_quotes(char c, int quotes) 
// {
//     if (c == '\"') {
//         if (!quotes)
//             return 1;  // Início de uma citação de aspas duplas
//         else if (quotes == 1)
//             return 0;  // Fim de uma citação de aspas duplas
//     } else if (c == '\'') {
//         if (!quotes)
//             return 2;  // Início de uma citação de aspas simples
//         else if (quotes == 2)
//             return 0;  // Fim de uma citação de aspas simples
//     }
//     return quotes;  // Retorna o estado atual de citação
// }


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

