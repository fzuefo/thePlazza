##
## EPITECH PROJECT, 2022
## myftp
## File description:
## Makefile
##



TARGET	:=		plazza

CXX		:=		g++
ifneq ("$(wildcard /bin/ccache)","")
	CXX	:=	ccache g++
endif


ifneq ("$(wildcard /bin/firefox)","")
	BROWSER	:=	firefox
endif

ifneq ("$(wildcard /bin/chromium)","")
	BROWSER	:=	chromium
endif

DOC_DEPS	:=	 	$(wildcard docs/doxygen/html/)

CXXFLAGS	:=		-Wall -Wextra --std=c++20

##-Werror

ifeq ("${ENV}", "dev")
    CXXFLAGS += -g3
else
	ifeq ("${ENV}", "staging")
		CXXFLAGS += -O2 -g3
	else
		CXXFLAGS += -O2
	endif
endif

VPATH	:=		src:inc

DEPS	:=		$(wildcard inc/*.hpp)

SRC		:=		main.cpp 	\
				PlazzaCore.cpp \
				ParseArg.cpp \
				AProcess.cpp  \
				load_balancer.cpp \
				Kitchen.cpp \
				Fifo.cpp \
				AIPC.cpp \
				PlazzaIpc.cpp \
				Pizza.cpp \
				Reception.cpp \
				Cook.cpp \
				Logger.cpp

OBJDIR	:=		obj

OBJ		:=		$(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

LDFLAGS	:=		-I inc -I inc/interfaces -pthread

all:	$(TARGET)
	@echo  -e "\e[32mlinking compliete\e[39m"

$(TARGET):	$(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: src/%.cpp $(DEPS)
	@$(CXX) -c -o $@ $(CXXFLAGS) $< $(LDFLAGS)
	@echo -e "\t\e[36mCompilate \e[3;97;4m$@\e[00m; \e[1;92mSUCCES\e[00m"


clean:
	@echo -e "\e[33m-->Cleaning time\e[00m"
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)
	rm -rf docs/doxygen/html
	rm -f docs.html

re: fclean all

build_docs: $(DEPS)
	doxygen docs/doxygen/doxygen.conf
	ln -rsf  docs/doxygen/html/index.html docs.html

docs:
	nohup $(BROWSER) docs.html &

test:
	echo $(DEPS)

.PHONY:	all clean fclean re build_docs docs
