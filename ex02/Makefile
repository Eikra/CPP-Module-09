NAME = PmergeMe

SRC = main.cpp #PmergeMe.cpp

OBJ = $(SRC:.cpp=.o)

CXX = c++

CXXFLAGS = -Wall -Werror -Wextra -std=c++98 

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ) #PmergeMe.hpp
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all