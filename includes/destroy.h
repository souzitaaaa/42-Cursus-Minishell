/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:41:52 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/17 15:12:34 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTROY_H
# define DESTROY_H

# include "minishell.h"

/*
!FREE_LIST.C
*/
void	free_quotes(t_quotes *stack);
void	free_lexer(t_lexer *stack);
void	free_env(t_env *stack);
void	free_list(t_node **head);

/*
!FREE_AST.C
*/
void    free_ast(t_ast	*ast);

/*
!DESTROY
*/
void    destroy_input(t_main *main);
void    destroy_main(t_main *main);

#endif
