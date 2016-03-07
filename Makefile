NAME	= rt

CC	= g++

RM	= rm -f

SRCDIR	= src/

INCDIR	= inc/

LIBINC = SimplexLib/inc/

OBJDIR	= obj/

LIBDIR 	= ./SimplexLib/build/

SRCS	= main.cpp \
				Parser.cpp \
				Parsable.cpp \
				Rt.cpp \
				SceneObj.cpp \
				Camera.cpp \
				Sphere.cpp \
				Window.cpp \
				Math.cpp \
				Light.cpp \
				LightModel.cpp \
				Rectangle.cpp \
				Color.cpp

OBJS	= $(addprefix $(OBJDIR), $(SRCS:.cpp=.o))

CXXFLAGS	= -O2 -march=native -std=c++14 -g

INCOMP = -I $(INCDIR) -I $(LIBINC)

LDFLAGS	= -lsfml-graphics -lsfml-window -lsfml-system -lm

LIB	= -L$(LIBDIR) -lSimplexNoise

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR))

$(OBJDIR)%.o:	$(SRCDIR)%.cpp
	$(CC) $(CXXFLAGS) $(INCOMP) -o $@ -c $<

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIB)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
