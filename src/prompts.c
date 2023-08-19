/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:32:26 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/19 17:12:37 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt_diogo(t_prompt *prompt_list)
{
	prompt_list->logname = ft_strjoin("[", prompt_list->logname);
	prompt_list->logname = ft_strjoin(prompt_list->logname, "]");
	prompt_list->pwd = ft_strjoin("[", prompt_list->pwd);
	prompt_list->pwd = ft_strjoin(prompt_list->pwd, "]");
	prompt_list->out = ft_strjoin(RGB_MIKU, COLOR_BOLD);
	prompt_list->out = ft_strjoin(prompt_list->out, prompt_list->logname);
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
	prompt_list->out = ft_strjoin(prompt_list->out, "\033[1;37m at \033[0m");
	prompt_list->out = ft_strjoin(prompt_list->out, RGB_MIKU_PINK);
	prompt_list->out = ft_strjoin(prompt_list->out, prompt_list->pwd);
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
	prompt_list->out = ft_strjoin(prompt_list->out, "\n");
	prompt_list->out = ft_strjoin(prompt_list->out, RGB_MIKU_ARROW);
	prompt_list->out = ft_strjoin(prompt_list->out, " ➜ ");
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
	prompt_list->out = ft_strjoin(prompt_list->out, COLOR_OFF);
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
}

void	prompt_rita(t_prompt *prompt_list)
{
	prompt_list->logname = ft_strjoin("(", prompt_list->logname);
	prompt_list->logname = ft_strjoin(prompt_list->logname, ")");
	prompt_list->pwd = ft_strjoin("(", prompt_list->pwd);
	prompt_list->pwd = ft_strjoin(prompt_list->pwd, ")");
	prompt_list->out = ft_strjoin(WHITE, "┎");
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
	prompt_list->out = ft_strjoin(prompt_list->out, RGB_GREEN);
	prompt_list->out = ft_strjoin(prompt_list->out, prompt_list->pwd);
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
	prompt_list->out = ft_strjoin(prompt_list->out, WHITE);
	prompt_list->out = ft_strjoin(prompt_list->out, "───────");
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
	prompt_list->out = ft_strjoin(prompt_list->out, RGB_PINK);
	prompt_list->out = ft_strjoin(prompt_list->out, prompt_list->logname);
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
	prompt_list->out = ft_strjoin(prompt_list->out, "\n");
	prompt_list->out = ft_strjoin(prompt_list->out, WHITE);
	prompt_list->out = ft_strjoin(prompt_list->out, "┃\n");
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
	prompt_list->out = ft_strjoin(prompt_list->out, WHITE);
	prompt_list->out = ft_strjoin(prompt_list->out, "┖ minihell🔥 ");
	prompt_list->out = ft_strjoin(prompt_list->out, RESET);
}
