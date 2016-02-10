all: dirtest linux

EXENAME=SpecialBitter
LIBDIR=./lib
BINDIR=./bin
OBJDIR=./obj
SRCDIR=./src
INCDIR=./include
LA_INCDIR=../include
CFLAGS=-I$(LA_INCDIR) -I$(INCDIR) -I/usr/include/freetype2 -std=c++11 $(ESFLAGS) -c
LFLAGS=-std=c++11
LIBS=-lfreetype -lftgl -lX11 -lGLU -lGL -lEngineMk1 
CC=mpic++
INCLUDES=$(wildcard $(INCDIR)/*.hpp)
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(subst $(SRCDIR),$(OBJDIR),$(patsubst %.cpp,%.o,$(SRC)))

clean:
	-rm $(OBJDIR)/*.o
	-rm $(BINDIR)/*

#dirtest: make directories $(OBJDIR) and $(WOBJDIR) in case they don't already exist
dirtest:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	$(CC) $(CFLAGS) $< -o $@

linux: $(OBJS) $(BINDIR)/$(EXENAME)

$(BINDIR)/$(EXENAME):  $(OBJS) ../EngineMk1/lib/libEngineMk1.a
	$(CC) $(LFLAGS) -I$(INCDIR)  $(OBJS) $(LIBS) -o $(BINDIR)/$(EXENAME)


