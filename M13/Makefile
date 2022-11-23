# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 14:52:36 by marvin            #+#    #+#              #
#    Updated: 2022/06/07 14:52:36 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Folders and Names
NAME		= minishell
SRCSDIR		= srcs
OBJSDIR		= objs
EXTLIB		= libft


SRCS		= main.c builtin.c parse.c exebash.c stack.c in_out.c cd.c execv.c lexer.c\

# Compiler options
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
DFLAG		= -lreadline

###################################################
# The rest is done by the MakeFile automatically, #
# you should not have to modify it				  #
###################################################
OBJS	= $(SRCS:%.c=$(OBJSDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(EXTLIB)/$(EXTLIB).a
	@echo "Assembling $@"
	@$(CC) $(CFLAGS) $(DFLAG) -o $@  $^

$(OBJS): $(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@echo Compiling $<
	@$(CC) $(CFLAGS) -I$(EXTLIB)/incs -c $< -o $@

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