/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:29:26 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/10 16:59:31 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_group/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <time.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

typedef enum s_type
{
	PIPE,     // |
	HEREDOC,  // << 
	APPEND,   // >> 
	OUT,      // >
	IN,       // <
	STRING,   // string (pode ser comando, ficheiro)
}t_type;

typedef struct s_node
{
	struct s_node	*prev;
	char	*array; //se o tipo for um careter especial o array pode ser NULL?
	t_type	type;
	int		index;
	struct s_node	*next;
}t_node;

typedef struct s_list
{
	struct s_node	*head;
	int				size;
}t_list;

typedef struct s_main
{
	t_list			tokens;
	char 			*input_prompt;
}t_main;

/*
List stuff
*/
void		shift_index(t_list *stack);
void		put_head_node(t_list *stack, t_node *new);
t_node		*remove_head(t_list *stack);
void		insert_head(t_list *stack, t_node *new);
void		free_stack(t_list *stack);
void		create_stack(t_list *stack);
void		insert_last(t_list *stack, t_node *new);

void	lexer(t_main *main);

#endif
