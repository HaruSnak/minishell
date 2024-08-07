/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcardin <pcardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:33:59 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/31 16:58:44 by pcardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/includes/libft.h"
# include "exec.h"

// DEBUG MACROS 
/*# define PL fprintf(stderr, "file: %s line: %d pid: %i\n", \
	__FILE__, __LINE__, getpid())
/*# define PI(x) fprintf(stderr, "PI: %d\n", (x));
# define PS(x) fprintf(stderr, "PS: %s\n", (x));
# define PI2(s, x) fprintf(stderr, "%s: %d\n", (s), (x));
# define PS2(s, x) fprintf(stderr, "%s: %s\n", (s), (x));
*/
# define PROMPT "\001\033[0;32m\002minishell\001\033[0m\002$ "

# define TRUE 1
# define FALSE 0

# define IN 1
# define OUT 2
# define APPEND 3
# define HEREDOC 4
# define PIPE 5
# define CMD 6
# define ARG 7
# define FILE 8

// Variable globale
extern int	g_signal_number;

typedef struct s_quote
{
	bool	check_s;
	bool	check_d;
	int		p;
}	t_quote;

typedef struct s_heredoc_state
{
	int		active;
	int		interrupted;
}	t_heredoc_state;

typedef struct s_parsing
{
	bool	quote_heredoc;
	char	**tkn;
	char	**tmp_setenv;
	char	*n_senv;
	char	*v_senv;
	char	*pwd;
	int		*tkn_value;
	int		count_envp;
	int		exit_value;
	int		stdout_cpy;
	t_quote	*quote;
}	t_parsing;

// PARSING FUNCTIONS
char	*ft_separe_operator(char *input);
int		ft_token_value(t_parsing *parsing);
int		ft_check_odd_quote(char *input, t_parsing *parsing);
char	*ft_f_null_q(t_parsing *parsing, char *env_var, int i, int p);
int		ft_condition_envp(t_parsing *parsing, char **envp, char *env, int i);
void	ft_verify_quote(t_parsing *parsing, int i, int k);
void	ft_delete_quote(t_parsing *parsing);

// SIGNALS FUNCTIONS
void	ft_signal_handler(int signum);
void	ft_signal_quit(int signum);
void	ft_signal_return(int signum);
void	ft_init_signal(struct sigaction *sa, struct sigaction *sa_quit);
void	ft_init_signal_block(void);
void	ft_init_signal_heredoc(void);
void	ft_signal_heredoc(int signum);
void	ft_exec_signals_main(struct sigaction sa, struct sigaction sa_quit);
void	ft_exec_signals_block(struct sigaction sa_return,
			struct sigaction sa_quit, t_exec *data);
int		ft_g_signal(t_parsing *parsing);

// COMMANDS FUNCTIONS
int		builtins_exec(t_parsing *parsing, char **envp);
char	*ft_split_input(char *input, char *c);
int		ft_setenv(char **envp, t_parsing *parsing);

// BUILTINS CD FUNCTIONS
void	ft_handle_cd_home(t_parsing *parsing, char **envp);
void	ft_handle_cd_previous(t_parsing *parsing, char **envp);
void	ft_cd_previous_bis(t_parsing *parsing, char **envp, char *path);
void	ft_handle_cd_root(t_parsing *parsing, char **envp);
void	ft_handle_cd_oldpwd(t_parsing *parsing,
			char **envp, char *path, char *oldpwd);
void	ft_handle_cd_path(t_parsing *parsing, char **envp);

// BUILTINS EXPORT UNSET FUNCTIONS
int		ft_handle_unset(t_parsing *parsing, char **envp);
void	ft_handle_export(t_parsing *parsing, char **envp);

// BUILTINS EXTERNALS FUNCTIONS
int		ft_handle_empty_cmd(char **input);
int		ft_handle_exit(t_parsing *parsing);
bool	is_builtins(char *cmd, t_exec *data, char **envp);
void	ft_cmd_clear(void);
void	ft_cmd_env(char **envp);
void	reset_std_out(t_parsing *parsing_ptr);

// REDIRECTION FUNCTIONS SHELL
int		ft_handle_verify(char **input, t_parsing *parsing, char **envp);

// ERRORS FUNCTIONS
void	ft_end_verify(t_parsing *parsing);
void	ft_free_and_compact(char **str, int index, int size);
int		ft_error_quote(t_parsing *parsing, int s_quote, int d_quote);
void	ft_free_d_ptr(void ***ptr);
int		ft_error_operator(t_parsing *parsing);
int		ft_error_cmd_ext(int fd, char *str);
void	malloc_error_ptr(void *str, char *msg);
void	malloc_error_dbl_ptr(char **str, char *msg);

// QUOTE FUNCTIONS SHELL
int		ft_interpret_env(char **envp, t_parsing *parsing);
int		ft_return_value_quote(t_parsing *parsing, int k);
int		ft_quote_empty_pipe(t_parsing *parsing, int i);

// UTILS FUNCTIONS
int		ft_count_index(char **input);
int		ft_strlen_quote(t_parsing *parsing, char *str, char c, int i);
int		ft_strlen_quote_b(char *str, char c, int i);
int		ft_check_envp(char **envp);
void	ft_check_redir(t_parsing *parsing);
int		ft_strlen_redic(char *str);

#endif