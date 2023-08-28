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

    printf("\033[1;35m\t\t[Quotes analises]\033[0m\n");
    while (main->input_prompt[i] != '\0') 
    {
        char c = main->input_prompt[i];
        quotes_analises = check_quotes(c, quotes_analises);

        if (c == '\'' || c == '\"')
        {
            if (quotes_analises == 1 && open_quote_position == -1)
            {
                open_quote_position = i;
                open_quote_type = c;
            }
            else if (quotes_analises == 0 && open_quote_position != -1)
            {
                printf("Open quote of type %c at position %d, Close quote at position %d\n", open_quote_type, open_quote_position, i);
                main->quotes.type = open_quote_type;
				main->quotes.start = open_quote_position;
				main->quotes.end = i;
				open_quote_position = -1; // Reset da posição da aspa de abertura
                open_quote_type = '\0';   // Reset do tipo da aspa de abertura
            }
        }

        printf("Character: %c, Quotes state: %d\n", c, quotes_analises);
        i++;
    }

    if (quotes_analises == 1 || quotes_analises == 2)
    {
        printf("%s", SYNTAX_ERROR);
        main->quotes.error = 1;
    }
    ft_printf("\n");
    return 0;
}

/**
 * Aguarda a conclusão de processos filho e atualiza o status de saída.
 *
 * Esta função aguarda a conclusão de processos filho do shell. Ela lida
 * com os códigos de status retornados por esses processos e atualiza o
 * status de saída do shell, levando em consideração se um processo foi
 * interrompido por um sinal. Também lida com a atualização do status de saída
 * quando ocorre uma interrupção de sinal específica. Além disso, atualiza o contador
 * de processos em execução.
 *
 * @param main Um ponteiro para a estrutura do t_main.
 */
void ft_wait(t_main *main) 
{
    int status; // Variável para armazenar o status do processo filho.
    if (waitpid(main->pid, &status, 0) != -1)  // Aguarda a conclusão do processo filho e obtém o status.
    {
        if (WIFSIGNALED(status)) // Verifica se o processo filho foi encerrado por um sinal.
        {
            if (status == 131)// Se o sinal for 131 (SIGQUIT), atualiza o status de saída.
                g_ex_status = status;
            else
                status += 128; // Atualiza o status com um valor de sinal.
        }
        if (main->fork)// Se o processo foi criado usando fork, atualiza o status de saída.
            g_ex_status = status;
        if (g_ex_status == 130)// Se o status de saída for 130 (SIGINT), exibe uma nova linha.
            ft_putchar_fd('\n', STDOUT_FILENO);
        main->proc--; // Decrementa o contador de processos em execução.
    }
    while (main->proc) {// Enquanto ainda houver processos em execução.
        signal(SIGQUIT, signal_quit);// Define o manipulador de sinal para SIGQUIT (Ctrl+\).
        wait(0);// Aguarda a conclusão de um processo filho.
        main->proc--;// Decrementa o contador de processos em execução.
    }
    if (g_ex_status > 255)// Normaliza o status de saída se for maior que 255.
        g_ex_status = g_ex_status / 255;
}
