/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:39:41 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/31 15:47:40 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal_number = 0;

void	ft_init_main(t_parsing *parsing, t_quote *quote, char **envp, int argc)
{
	parsing->quote = quote;
	parsing->exit_value = 0;
	parsing->pwd = getenv("PWD");
	parsing->tmp_setenv = NULL;
	parsing->n_senv = "OLDPWD";
	parsing->v_senv = "";
	parsing->quote_heredoc = false;
	parsing->count_envp = ft_check_envp(envp);
	parsing->stdout_cpy = dup(1);
	quote->check_d = false;
	quote->check_s = false;
	quote->p = 0;
	ft_setenv(envp, parsing);
	(void)argc;
}

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	struct sigaction	sa;
	struct sigaction	sa_quit;
	t_parsing			parsing;
	t_quote				quote;

	ft_init_main(&parsing, &quote, envp, argc);
	(void)argv;
	ft_init_signal(&sa, &sa_quit);
	input = NULL;
	while (1)
	{
		ft_exec_signals_main(sa, sa_quit);
		input = readline(PROMPT);
		ft_g_signal(&parsing);
		if (!input)
			break ;
		add_history(input);
		ft_handle_verify(&input, &parsing, envp);
		free(input);
		input = NULL;
	}
	if (parsing.tmp_setenv != NULL)
		ft_free_d_ptr((void ***)&parsing.tmp_setenv);
	return (0);
}
