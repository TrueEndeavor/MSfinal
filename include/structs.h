/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:49:22 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/11 14:37:50 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define MAXARGS 20

# define IS_A_VARIABLE 1
# define IS_NOT_A_VARIABLE 0

# define IS_A_POSSIBLE_NAME 1
# define IS_NOT_A_POSSIBLE_NAME 0

/*---------------------- Structures for Lexer & Token  ----------------------*/
typedef enum TOKEN_TYPE_ENUM
{
	T_START = 0,
	T_WORD = 1,
	T_DOLLAR = 2,
	T_VARIABLE = 3,	
	T_IO_NUMBER = 4,
	T_PIPE = 5,
	T_REDIRECT_IN = 6,
	T_REDIRECT_OUT = 7,
	T_HEREDOC = 8,
	T_APPEND_OUT = 9,
	T_LINEBREAK = 10,
	T_EXITCODE = 11
}	t_token_type_E;

typedef struct TOKEN_STRUCT
{
	int					type;
	char				*value;
	struct TOKEN_STRUCT	*next;
}	t_token_T;

typedef struct LEXER_STRUCT
{
	char				*src;
	size_t				src_size;
	char				c;
	unsigned int		i;
}	t_lexer_T;

/*----------------- Structures for Syntax Analyser  -----------------*/

/* State Transition Diagram (STT)
/--------------------------------\
| State | Condition | Next State |
|-------|-----------|------------|
|  q0   |   word    |     q1     |
|  q0   |   redir   |     q2     |
|  q1   |   word    |     q1     |
|  q1   |   pipe    |     q3     |
|  q1   |   redir   |     q2     |
|  q2   |   word    |     q1     |
|  q3   |   word    |     q1     |
|  q3   |   redir   |     q2     |
/--------------------------------\ */

typedef enum STATE_ENUM
{
	STATE_Q0 =0,
	STATE_Q1 = 1,
	STATE_Q2 = 2,
	STATE_Q3 = 3,
	STATE_ERROR = 4
}	t_state_enum;

/*---------------------- Structures for Parser  ----------------------*/
typedef enum PARSER_CMD_ENUM
{
	EXEC_CMD = 1,
	REDIR_CMD = 2,
	PIPE_CMD = 3,
	HERE_CMD = 4	
}	t_parser_cmd_E;

/* Base structure */
typedef struct CMD
{
	t_parser_cmd_E		type;
}	t_cmd_P;

/* Derived structures */
typedef struct EXECCMD
{
	int					type;
	char				*argv[MAXARGS];
}	t_execcmd_P;

typedef struct REDIRCMD
{
	int					type;
	struct CMD			*cmd;
	char				*file;
	int					mode;
	int					fd;
	int					permission;
	int					read_from;		
	int					write_into;	
}	t_redircmd_P;

typedef struct PIPECMD
{
	int					type;
	struct CMD			*left;
	struct CMD			*right;
}	t_pipecmd_P;

typedef struct HERECMD
{
	int					type;
	struct CMD			*cmd;
	char				*delimiter;
	char				*filename;
	int					fd;
}	t_herecmd_P;

/*---------------------- Structures for Minishell  ----------------------*/
typedef struct ENVLIST
{
	char				*name;
	char				*value;
	struct ENVLIST		*next;
}	t_env_list;

typedef struct CORESTRUCT
{
	t_env_list				*env_list;
	t_token_T				**token_head;
	int						exit_code;
	int						ih;
	t_cmd_P					*hcmd[20];
}	t_core_struct;

typedef struct DATA
{
	t_core_struct	*core;
	t_cmd_P			*fcmd;
}	t_data;

#endif
