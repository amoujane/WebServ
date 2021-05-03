# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amoujane <amoujane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 16:32:57 by amoujane          #+#    #+#              #
#    Updated: 2021/05/03 16:32:59 by amoujane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	main.cpp \
		srcs/server.cpp \
		srcs/headers.cpp \
		srcs/init_servers.cpp \
		srcs/location.cpp \
		srcs/autoindex.cpp \
		srcs/extra_functions.cpp \
		srcs/cgi_env.cpp \
		srcs/client.cpp

HEADERS = 	includes/cgi_env.hpp \
			includes/client.hpp \
			includes/extra.hpp \
			includes/header.hpp \
			includes/headers.hpp \
			includes/location.hpp \
			includes/server.hpp 

NAME = webserv

FLAG = -std=c++98 -Wall -Werror -Wextra

COMP = clang++

RED		= \033[0;31m
NC		= \033[0m
BLUE	= \033[0;34m
GREAN	= \033[0;32m
YELLOW	= \033[0;33m

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): 	$(OBJ) $(HEADERS)
					$(COMP) $(FLAG) $(OBJ) -o $(NAME)
					@echo "$(GREAN)webserv Created$(NC)"

%.o: %.c
					@$(COMP) $(FLAG) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "${RED}Object files has been removed${NC}"

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}webserv removed${NC}"

re: fclean all