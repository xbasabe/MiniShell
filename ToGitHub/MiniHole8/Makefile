# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 14:52:36 by marvin            #+#    #+#              #
#    Updated: 2023/12/05 11:14:42 by xbasabe-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Folders and Names
NAME		= minishell
SRCSDIR		= srcs
OBJSDIR		= objs
EXTLIB		= libft
READLINE_DIR = ${HOME}/.brew/opt/readline


#SRCS		= main.c signals.c

SRCS		= main.c signals.c builtin.c parse.c exebash.c stack.c in_out.c cd.c execv.c chain.c export.c enviroment.c lst_env.c export_utils.c lst_env_two.c open_quotes2.c \
			  parse_utils.c parse2.c lexer_utils.c redirect.c lexer.c split_tokens.c split_lines.c ft_flag_split.c lines.c open_quotes.c redirect_node.c redirect_f_b.c cd_utils.c cd_utils2.c
		

# Compiler options
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
#DFLAG		= -lreadline
F_READLINE	= -I$(READLINE_DIR)/include
DFLAG		= -lreadline -L$(READLINE_DIR)/lib

###################################################
# The rest is done by the MakeFile automatically, #
# you should not have to modify it				  #
###################################################

OBJS = $(SRCS:%.c=$(OBJSDIR)/%.o)

all:$(NAME)

$(NAME): $(OBJS) $(EXTLIB)/$(EXTLIB).a
	@echo "Assembling $@"
	@$(CC) $(CFLAGS) -o $@  $(DFLAG)   $^

$(OBJS): $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling $<
	$(CC) $(CFLAGS) $(F_READLINE) -I$(EXTLIB)/incs -c $< -o $@

$(EXTLIB)/$(EXTLIB).a:
	@echo "Compiling $@"
	@$(MAKE) -s -C $(EXTLIB) > /dev/null

clean:
	rm -rf $(OBJSDIR)
	@$(MAKE) -s -C $(EXTLIB) clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -s -C $(EXTLIB) fclean

re: fclean all

.PHONY: all clean fclean re test
