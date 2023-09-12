/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:59 by joe               #+#    #+#             */
/*   Updated: 2023/09/12 13:01:15 by rimarque         ###   ########.fr       */
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
        //rl_replace_line("", 0);  // Substitui a linha atual por uma string vazia
        rl_on_new_line();        // Move o cursor para uma nova linha
        rl_redisplay();          // Redisplay o prompt
    }
}

/**
 * Manipulador de sinal para o sinal SIGINT (interrupção do terminal).
 *
 * Esta função é chamada quando o processo recebe um sinal SIGINT, que é
 * geralmente enviado quando o usuário pressiona Ctrl+C no terminal. Ela
 * exibe uma nova linha, atualiza o status de saída para 130, limpa a linha
 * atual, exibe uma nova linha e restaura o comportamento padrão do sinal SIGQUIT.
 *
 * @param sig O número do sinal recebido, geralmente SIGINT.
 */
void signal_quit1(int sig)
{
    if (sig == SIGINT)
    {
        ft_printf("\n");                  // Escreve uma nova linha no terminal
        g_ex_status = 130;                // Define o status de saída como 130
        rl_replace_line("", 0);           // Substitui a linha atual por uma string vazia
        rl_on_new_line();                 // Move o cursor para uma nova linha
        signal(SIGQUIT, SIG_DFL);        // Restaura o comportamento padrão do sinal SIGQUIT
    }
}

//!-----------------------> CRTL + \ <--------------------------
/**
 * Manipulador de sinal para o sinal SIGQUIT (sair do terminal com despejo de núcleo).
 *
 * Esta função é chamada quando o processo recebe um sinal SIGQUIT, que é
 * geralmente enviado quando o usuário pressiona Ctrl+\ no terminal. Ela
 * exibe uma nova linha, atualiza o status de saída para 131, limpa a linha
 * atual, exibe uma nova linha, imprime a mensagem "Quit: (core dumped)"
 * e restaura o comportamento padrão do sinal SIGQUIT.
 *
 * @param sig O número do sinal recebido, geralmente SIGQUIT.
 */
void signal_quit(int sig)
{
    if (sig == SIGQUIT)
    {
        write(1, "\n", 1);                 // Escreve uma nova linha no terminal
        g_ex_status = 131;                // Define o status de saída como 131
        rl_replace_line("", 0);           // Substitui a linha atual por uma string vazia
        rl_on_new_line();                 // Move o cursor para uma nova linha
        ft_printf("Quit: (core dumped)\n"); // Imprime a mensagem "Quit: (core dumped)"
        signal(SIGQUIT, SIG_DFL);         // Restaura o comportamento padrão do sinal SIGQUIT
    }
}

/**
 * Manipulador de sinal para o sinal SIGQUIT (sair do terminal com despejo de núcleo).
 *
 * Esta função é chamada quando o processo recebe um sinal SIGQUIT, que é
 * geralmente enviado quando o usuário pressiona Ctrl+\ no terminal. Ela
 * atualiza o status de saída para 131 e ignora futuros sinais SIGQUIT.
 *
 * @param sig O número do sinal recebido, geralmente SIGQUIT.
 */
void signal_quit2(int sig) {
    if (sig == SIGQUIT) {
        g_ex_status = 131;            // Define o status de saída como 131
        signal(SIGQUIT, SIG_IGN);     // Ignora futuros sinais SIGQUIT
    }
}


/**
 * Configura os manipuladores de sinal para SIGINT e SIGQUIT.
 *
 * Esta função associa manipuladores de sinal específicos para os sinais
 * SIGINT e SIGQUIT. Ela utiliza a função signal_handler para SIGINT e
 * ignora SIGQUIT.
 */
void signals(void)
{
    signal(SIGINT, signal_handler);     // Associa signal_handler ao sinal SIGINT
    signal(SIGQUIT, SIG_IGN);           // Ignora o sinal SIGQUIT
}
