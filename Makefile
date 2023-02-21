# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chduong <chduong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 17:16:04 by chduong           #+#    #+#              #
#    Updated: 2023/02/21 23:03:23 by chduong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
#		EXEC, COMMANDS & FLAGS			#
#########################################
NAME		= 	ft_container
STD			=	std_container

CXX			=	c++ -c
CXXFLAGS	=	-Wall -Wextra -Werror $(VERSION) $(INC) $(DPFLAG)
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
SRC			=	main.cpp \
				test_map.cpp \
				test_set.cpp \
				test_vector.cpp \
				test_stack.cpp

STDSRC		= 	main_std.cpp \
				test_map_std.cpp \
				test_set_std.cpp \
				test_vector_std.cpp \
				test_stack_std.cpp	

SRC_DIR		=	src/
OBJ_DIR		=	obj/
OBJ			=	$(SRC:%.cpp=%.o)
OBJ			:=	$(addprefix $(OBJ_DIR), $(OBJ))

STDOBJ		=	$(STDSRC:%.cpp=%.o)
STDOBJ		:=	$(addprefix $(OBJ_DIR), $(STDOBJ))

DEP			=	${OBJ:.o=.d}

#########################################
#			MAKE	RULES				#
#########################################
all: $(NAME) $(STD)

$(NAME): $(OBJ)
	@$(LINK) $(OBJ) -o $@ 
	@echo "> $(CYAN)Compilation FT TEST$(END) : \t\t[$(YELLOW)COMPLETE$(END)]"

$(STD): $(STDOBJ)
	@$(LINK) $(STDOBJ) -o $@ 
	@echo "> $(CYAN)Compilation STD TEST$(END) : \t\t[$(YELLOW)COMPLETE$(END)]"
	
-include ${DEP}

${OBJ_DIR}%.o:	${SRC_DIR}%.cpp
	@${MKDIR} ${@D}
	${CXX} ${CXXFLAGS} -std=c++98 $< -o $@


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