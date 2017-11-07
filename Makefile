NAME = Pacman

FLAGS = -Wall -Wextra -Werror -std=c++0x

SRC = main.cpp Map.cpp Balls.cpp Enemy.cpp Pacman.cpp Text.cpp functions.cpp

OB = $(SRC:.cpp=.o)

FR = -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(NAME)

$(NAME): $(OB)
			@clang++ $(OB) $(FLAGS) $(FR) -o $(NAME)
			@ echo "                                        "'\r\c'
			@echo "Project was compiled"

%.o: %.cpp
			@clang++ -c -o $@ $< $(FLAGS)
			@ echo "Compile $<" '\r\c'

clean:
			@rm -f $(OB)
			@echo "Deleted *.o"

fclean: clean
			@rm -f $(NAME)
			@echo "Deleted all"

re: clean all


