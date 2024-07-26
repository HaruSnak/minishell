/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:41:10 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/26 16:56:32 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Verify the operators in the input
// Add the token value to the parsing structure
// Handle the verify process for the minishell program
// Return 0 if the process is successful
int	ft_handle_verify(char **input, t_parsing *parsing, char **envp)
{
	if (ft_handle_empty_cmd(input) == -1)
		return (0);
	if (ft_check_odd_quote(*input, parsing) == -1)
		return (-1);
	*input = ft_separe_operator(*input);
	parsing->tkn = ft_split_tkn(*input, ' ');
	if (ft_error_operator(parsing) == -1)
		return (ft_free_d_ptr((void ***)&parsing->tkn), -1);
	ft_interpret_env(envp, parsing);
	ft_token_value(parsing);
	ft_delete_quote(parsing);
	if (ft_check_redir(parsing) == 0 && builtins_exec(parsing, envp) == 0)
		return (ft_end_verify(parsing), -1);
	else
		execution(parsing->tkn, envp, parsing);
	ft_end_verify(parsing);
	return (0);
}
