# compiler flags
CC=gcc
CFLAGS=-Iinc --std=c99 -O3
CLFLAGS=-lglfw -lGLEW -lpng

# directory settings
SRCDIR=src
INCDIR=inc
BINDIR=bin
OBJDIR=obj
DEPDIR=deps
DOCDIR=docs
RESDIR=res

# file lists
SOURCES_RAW=creep.c geometry.c main.c map.c texture.c tile.c tower.c towerdef.c window.c
SOURCES=$(addprefix $(SRCDIR)/, $(SOURCES_RAW))
DEPS=$(subst $(SRCDIR)/,$(DEPDIR)/,$(SOURCES:.c=.d))
OBJS=$(subst $(SRCDIR)/,$(OBJDIR)/,$(SOURCES:.c=.o))

HEADERS_RAW=creep.h geometry.h map.h texture.h tile.h tower.h towerdef.h window.h util.h
HEADERS=$(addprefix $(INCDIR)/, $(HEADERS_RAW))

# main targets

all: towerdef

clean:
	rm -f $(DEPS)
	rm -f $(OBJS)
	rm -rf $(DOCDIR)

depend: $(DEPS)

docs: $(HEADERS)
	doxygen doxygen.conf

resources:
	rsync -r $(RESDIR) $(BINDIR)

run: towerdef
	bin/towerdef
	
towerdef: $(OBJS) resources
	$(CC) $(CFLAGS) -o $(BINDIR)/towerdef $(OBJS) $(CLFLAGS)

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
