# compiler flags
CC=gcc --std=c99 -O3
CFLAGS=-Iinc
CLFLAGS=-lglut -lGLEW -lpng

# directory settings
SRCDIR=src
INCDIR=inc
BINDIR=bin
OBJDIR=obj
DEPDIR=deps
DOCDIR=docs
RESDIR=res

# file lists
SOURCES_RAW=towerdef.c window.c texture.c
SOURCES=$(addprefix $(SRCDIR)/, $(SOURCES_RAW))
DEPS=$(subst $(SRCDIR)/,$(DEPDIR)/,$(SOURCES:.c=.d))
OBJS=$(subst $(SRCDIR)/,$(OBJDIR)/,$(SOURCES:.c=.o))

HEADERS_RAW=towerdef.h window.h texture.h util.h
HEADERS=$(addprefix $(INCDIR)/, $(HEADERS_RAW))

# main targets

all: towerdef

run: towerdef
	bin/towerdef
	
towerdef: $(OBJS) resources
	$(CC) $(CFLAGS) -o $(BINDIR)/towerdef $(OBJS) $(CLFLAGS)

resources:
	rsync -r $(RESDIR) $(BINDIR)

clean:
	rm -f $(DEPS)
	rm -f $(OBJS)
	rm -rf $(DOCDIR)

depend: $(DEPS)

docs: $(HEADERS)
	doxygen doxygen.conf

# dependency generation
$(DEPDIR)/%.d: $(SRCDIR)/%.c
	@set -e rm -r $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(OBJDIR)/\1.o $@ : , g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# obj compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

# dependency includes
-include $(DEPS)
