
#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/includes/libft.h"

# define PL printf("file:%s line: %d\n", __FILE__, __LINE__)

# define TRUE 1
# define FALSE 0

# define IN 0
# define OUT 1
# define APPEND 2
# define HEREDOC 3
# define PIPE 4
# define CMD 5
# define FILE 6

extern int g_signal;

struct s_parsing
{
	char	**tkn;
	int		**tkn_value;
	char	**path;
	char	**tmp_env;
	char	*tkn_cpy;
	char	*n_senv;
	char	*v_senv;
	char	*cmd_path;
	char	*input;
	char	*pwd;
	char	*tmp;
	int		exit_value;
	int		status;

	char	*infile;
	char	*outfile;
	int		fds[2];
	int		prevpipe;
	pid_t	pidz[1];
};

// EXECUTION
void	execution(char *argv[], char **envp, struct s_parsing *parsing);
void	child_exec(char **envp,  struct s_parsing *parsing, int i, char *path);

// Execution Utils
char	**ft_path_envp(char **envp);
void	wait_pidz(struct s_parsing *parsing);
void	check_err_fork(pid_t pid);
char	*find_cmd_path(struct s_parsing *parsing, int i);
int		is_cmd(char *path);

// PARSING FUNCTIONS 
int		ft_find_execve(char **envp, struct s_parsing *parsing);
int		ft_if_execve_access(struct s_parsing *parsing, char **envp);

// SIGNALS FUNCTIONS
void	ft_signal_handler(int signo);

// COMMANDS FUNCTIONS
int		ft_external_cmds(char **input, struct s_parsing *parsing, char **envp);
char	*ft_split_input(char *input, char *c);
int		ft_setenv(char **envp, struct s_parsing *parsing);

// COMMANDS CD FUNCTIONS
void	ft_handle_cd_home(struct s_parsing *parsing,
			char **envp);
void	ft_handle_cd_previous(struct s_parsing *parsing,
			char **envp);
void	ft_handle_cd_root(struct s_parsing *parsing,
			char **envp);
void	ft_handle_cd_oldpwd(struct s_parsing *parsing,
			char **envp, char *path, char *oldpwd);
void	ft_handle_cd_path(struct s_parsing *parsing, char **envp, char **input);

// COMMANDS EXPORT UNSET FUNCTIONS
int		ft_external_cmds_bis(char **input,
			struct s_parsing *parsing, char **envp);

// COMMANDS EXTERNALS FUNCTIONS
int		ft_handle_empty_cmd(char **input);
int		ft_handle_exit(char **input, struct s_parsing *parsing);
int		ft_handle_echo(char *input, struct s_parsing *parsing);

// REDIRECTION FUNCTIONS SHELL
int		ft_handle_verify(char **input, struct s_parsing *parsing, char **envp);
int		ft_exec_cmd_redirects(char **tmp, struct s_parsing *parsing);

// ERRORS FUNCTIONS
void	ft_end_verify(char **input, struct s_parsing *parsing);
void	ft_free_d_ptr(void **ptr);

#endif