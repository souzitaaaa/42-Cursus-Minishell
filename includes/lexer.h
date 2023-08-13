/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:03:41 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/13 15:33:40 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum s_type
{
	PIPE = '|',     // |
	IN = '<',       // <
	HEREDOC = 'H',  // <<
	OUT = '>',      // >
	APPEND = 'A',   // >>
	STRING = 'S',   // string (pode ser comando, ficheiro)
}t_type;

typedef struct s_node
{
	struct s_node	*prev;
	char	**token; //se o tipo for um careter especial o array pode ser NULL?
	t_type	type;
	int		index;
	struct s_node	*next;
}t_node;

typedef struct s_list
{
	struct s_node	*head;
	int				size;
}t_list;

#endif
