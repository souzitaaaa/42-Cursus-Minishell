/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:47:38 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/26 11:18:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_ex_status;
//tenho de fechar o hd, aqui e no main process
void	ft_redirect_in(t_node	*head, t_main *main, t_hd hd)
{
	t_node	*aux;

	aux = head;
	while (aux != NULL)
	{
		if (aux->token.type == HEREDOC && aux->index != hd.index)
			aux = aux->next;
		exec_rdr(aux->token, main, hd.fd);
		aux = aux->next;
	}
	if (hd.flag)
		close(hd.fd);
}

void	ft_heredoc(t_node *head, t_main *main, t_hd *hd)
{
	t_node	*aux;

	aux = head;
	while (aux != NULL)
	{
		if (aux->token.type == HEREDOC)
		{
			if (!hd->flag)
				hd->flag = true;
			else
				close(hd->fd);
			if (aux->token.arr[1] == NULL)
				hd->fd = open_hd(aux->token.arr[0], aux->token.quotes, main);
			else
				hd->fd = open_hd(aux->token.arr[1], aux->token.quotes, main);
			hd->index = aux->index;
		}
		if (g_ex_status == 130)
			return ;
		aux = aux->next;
	}
}

//percorre a arvore pela ordem de execucao e executa os hd
void	exec_hd_p(t_ast *ast, t_main *main)
{
	t_ast_node	*node;
	t_leaf		*leaf;

	node = get_beg(ast);
	while (node)
	{
		if (node->index == 0)
		{
			leaf = node->left;
			if (node->left->left != NULL)
				ft_heredoc(node->left->left, main, &leaf->hd);
			if (g_ex_status == 130)
				return ;
		}
		leaf = node->right;
		if (node->right->left != NULL)
			ft_heredoc(node->right->left, main, &leaf->hd);
		if (g_ex_status == 130)
			return ;
		node = node->prev;
	}
}
