all: dirtest linux linprof linopt

EXENAME=SpecialBitter
LIBDIR=./lib
BINDIR=./bin
OBJDIR=./obj
SRCDIR=./src
INCDIR=./include
LA_INCDIR=../include
CFLAGS=-I$(LA_INCDIR) -I$(INCDIR) -I/usr/include/freetype2 -std=c++11 $(ESFLAGS) -c
LFLAGS=-std=c++11
LIBS=-lfreetype -lftgl -lX11 -lGLU -lGL -lEngineMk1 -lpthread
LIBS_PROF=-lfreetype -lftgl -lX11 -lGLU -lGL -lEngineMk1P -lpthread
CC=g++
INCLUDES=$(wildcard $(INCDIR)/*.hpp)
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(subst $(SRCDIR),$(OBJDIR),$(patsubst %.cpp,%.o,$(SRC)))
OBJS_PROF=$(subst $(SRCDIR),$(OBJDIR),$(patsubst %.cpp,%.po,$(SRC)))
OBJS_OPT=$(subst $(SRCDIR),$(OBJDIR),$(patsubst %.cpp,%.oo,$(SRC)))

clean:
	-rm $(OBJDIR)/*.o
	-rm $(OBJDIR)/*.po
	-rm $(OBJDIR)/*.oo
	-rm $(BINDIR)/*

#dirtest: make directories $(OBJDIR) and $(WOBJDIR) in case they don't already exist
dirtest:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/%.po: $(SRCDIR)/%.cpp $(INCLUDES)
	$(CC) -g $(CFLAGS) $< -o $@ -pg

$(OBJDIR)/%.oo: $(SRCDIR)/%.cpp $(INCLUDES)
	$(CC) -O3 $(CFLAGS) $< -o $@

linux: $(OBJS) $(BINDIR)/$(EXENAME)

$(BINDIR)/$(EXENAME):  $(OBJS) ../EngineMk1/lib/libEngineMk1.a
	$(CC) $(LFLAGS) -I$(INCDIR)  $(OBJS) $(LIBS) -o $(BINDIR)/$(EXENAME)

$(BINDIR)/$(EXENAME)_opt:  $(OBJS_OPT) ../EngineMk1/lib/libEngineMk1.a
	$(CC) $(LFLAGS) -O3 -I$(INCDIR)  $(OBJS_OPT) $(LIBS) -o $(BINDIR)/$(EXENAME)_opt


$(BINDIR)/profexe:  $(OBJS_PROF) ../EngineMk1/lib/libEngineMk1P.a
	$(CC) -g $(LFLAGS) -I$(INCDIR)  $(OBJS_PROF) $(LIBS_PROF) -o $(BINDIR)/profexe  -pg

linprof: $(BINDIR)/profexe
linopt: $(BINDIR)/$(EXENAME)_opt
