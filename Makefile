NAME	= rt

CC	= g++

RM	= rm -f

SRCDIR	= src/

INCDIR	= inc/

OBJDIR	= obj/

SRCS	= main.cpp \
				Parser.cpp \
				SceneObj.cpp \
				Sphere.cpp \
				Window.cpp

OBJS	= $(addprefix $(OBJDIR), $(SRCS:.cpp=.o))

CXXFLAGS	= -O2 -march=native -std=c++1y

INCOMP = -I $(INCDIR)

LDFLAGS	= -lsfml-graphics -lsfml-window -lsfml-system -lm

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o:	$(SRCDIR)%.cpp
	$(CC) $(CXXFLAGS) $(INCOMP) -o $@ -c $<

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(LDFLAGS) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
