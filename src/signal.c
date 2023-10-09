/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:59 by joe               #+#    #+#             */
/*   Updated: 2023/10/04 14:48:58 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_ex_status;

//!-----------------------> CRTL + C <--------------------------
/**
 * Manipulador de sinal para o sinal SIGINT (interrupção do terminal).
 *
 * Esta função é chamada quando o processo recebe um sinal SIGINT, que é
 * geralmente enviado quando o usuário pressiona Ctrl+C no terminal. Ela
 * atualiza o status de saída para 130, limpa a linha atual, exibe uma nova linha
 * e redisplay o prompt.
 *
 * @param sig O número do sinal recebido, geralmente SIGINT.
 */
void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        g_ex_status = 130;       // Define o status de saída para 130
        ft_printf("\n");         // Escreve uma nova linha
        rl_replace_line("", 0);  // Substitui a linha atual por uma string vazia
        rl_on_new_line();        // Move o cursor para uma nova linha
        rl_redisplay();          // Redisplay o prompt
    }
}

void signal_handler_child(int sig)
{
    if (sig == SIGINT)
    {
        g_ex_status = 130;
        ft_printf("\n");
    }
}

void signal_handler_hd(int sig)
{
    if (sig == SIGINT)
    {
        ft_printf("\n");
        exit(0);
    }
}

void signal_handler_nothing(int sig)
{
    if (sig == SIGINT)
        g_ex_status = 130;
}
/**
 * Configura os manipuladores de sinal para SIGINT e SIGQUIT.
 *
 * Esta função associa manipuladores de sinal específicos para os sinais
 * SIGINT e SIGQUIT. Ela utiliza a função signal_handler para SIGINT e
 * ignora SIGQUIT.
 */
void signals(int options)
{
    if(options == 0)
        signal(SIGINT, signal_handler);
    else if(options == 1)
        signal(SIGINT, signal_handler_child);
    else if(options == 2)
        signal(SIGINT, signal_handler_hd);
	else if(options == -1)
		signal(SIGINT, signal_handler_nothing);
    signal(SIGQUIT, SIG_IGN);  // Ignora o sinal SIGQUIT
}
