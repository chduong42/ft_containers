# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chduong <chduong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 17:16:04 by chduong           #+#    #+#              #
#    Updated: 2023/02/20 14:30:26 by chduong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
#		EXEC, COMMANDS & FLAGS			#
#########################################
NAME		=	test
STD 		=	std

CXX			=	c++ -c
CXXFLAGS	=	-Wall -Wextra -Werror $(INC) $(DPFLAG)
VERSION		=	-std=c++98 
INC			=	-I inc
DPFLAG		=	-MMD -MP
DEBUG		=	-g3 -fsanitize=address,undefined

LINK		=	c++
LFLAGS		=	

MKDIR		=	mkdir -p
AR			=	ar rcs
RM			= 	rm -rf

VALGRIND	=	valgrind $(LEAK)
FD			=	--track-fds=yes
LEAK		=	--leak-check=yes --show-reachable=yes
MEMCHECK	=	--tool=memcheck

#########################################
#	SOURCES - OBJECTS - DEPENDENCIES	#
#########################################
SRC			=	main.cpp

SRC_DIR		=	src/
OBJ_DIR		=	obj/
OBJ			=	$(SRC:%.cpp=%.o)
OBJ			:=	$(addprefix $(OBJ_DIR), $(OBJ))
DEP			=	${OBJ:.o=.d}

#########################################
#			MAKE	RULES				#
#########################################
$(NAME): $(OBJ)
	@echo "> $(CYAN)Generate objects$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(LINK) $(LFLAGS) -o $@ $^
	@echo "> $(CYAN)Compilation$(END) : \t\t[$(YELLOW)COMPLETE$(END)]"

-include ${DEP}

${OBJ_DIR}%.o:	${SRC_DIR}%.cpp
	@${MKDIR} ${@D}
	${CXX} ${CXXFLAGS} -std=c++98 $< -o $@

obj/stdfunc_test.o: src/stdfunc_test.cpp
	@${MKDIR} ${@D}
	${CXX} ${CXXFLAGS} -std=c++11 $< -o $@

$(STD): obj/stdfunc_test.o
	@$(LINK) $(LFLAGS) -o $@ $^
	@echo "> $(CYAN)Compilation STD TEST$(END) : \t\t[$(YELLOW)COMPLETE$(END)]"

all: $(NAME)

check:
	$(VALGRIND) $(STD)

clean:
	@$(RM) $(OBJ_DIR)
	@echo "> $(PURPLE)Clean objects$(END) : \t\t[$(GREEN)OK$(END)]"
	
fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(STD)
	@echo "> $(PURPLE)Delete Exec$(END) : \t\t[$(GREEN)OK$(END)]"
	
re: fclean all

.PHONY: all clean fclean re

#########################################
#			SYNTAX COLORS				#
#########################################
GREY		=   $'\033[0;30m
RED			=   $'\033[0;31m
GREEN		=   $'\033[0;92m
YELLOW		=   $'\033[0;33m
BLUE		=   $'\033[0;34m
U_BLUE		=   $'\033[4;34m
PURPLE		=   $'\033[0;35m
CYAN		=   $'\033[0;96m
WHITE		=   $'\033[0;37m
END			=   $'\033[0;m
BOLD		=   $'\e[1m