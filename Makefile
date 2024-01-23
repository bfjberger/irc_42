NAME = ircserv
PASSWORD = password
PORT = 6667

CC = c++
#FLAGS = -Wall -Wextra -Werror -fsanitize=address -fpermissive -std=c++98 -I./srcs
FLAGS = -Wall -Wextra -Werror -pedantic -std=c++98
RM = /bin/rm -rf

BLUE = \033[0;34m
RED = \033[0;31m
WHITE = \033[0;97m

INCLUDE = -I ./includes/
INCLUDE += -I ./includes/Commands/

# include all subdirectory within the includes directory
# INCLUDE += $(shell find ./includes -type d | sed 's/^/-I /')

SRC_PATH = ./srcs/
FILES = main.cpp \
		Server/Server.cpp \
		Server/Parser.cpp \
		Server/Execution.cpp \
		Client.cpp \
		ACommand.cpp \
		Commands/Invite.cpp \
		Commands/Join.cpp \
		Commands/Kick.cpp \
		Commands/Kill.cpp \
		Commands/Mode.cpp \
		Commands/Nick.cpp \
		Commands/Oper.cpp \
		Commands/Part.cpp \
		Commands/Pass.cpp \
		Commands/Privmsg.cpp \
		Commands/Quit.cpp \
		Commands/Topic.cpp \
		Commands/User.cpp

SRCS = ${addprefix ${SRC_PATH}, ${FILES}}

OBJ_DIR = ./objs/
OBJS = $(FILES:.cpp=.o)
OBJ = ${addprefix ${OBJ_DIR}, ${OBJS}}

DIR_DUP = @mkdir -p ${@D}

${OBJ_DIR}%.o: ${SRC_PATH}%.cpp
	@${DIR_DUP}
	@$(CC) $(FLAGS) ${INCLUDE} -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) ${INCLUDE} $(OBJ) -o $(NAME)
	@echo "${BLUE}Compiled executable${WHITE}"

run: $(NAME)
	./$(NAME) $(PORT) $(PASSWORD)

clean:
	@(${RM} $(OBJ_DIR))
	@echo "${RED}Clean objects files${WHITE}"

fclean: clean
	@(${RM} $(NAME))
	@echo "${RED}Clean executable files${WHITE}"

re: fclean all

.PHONY: all clean fclean re run