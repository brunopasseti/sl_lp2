CC=gcc
CFLAGS=-I -O1

SRCDIR = src
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

sl: $(OBJS)
	@echo  "=== Linking all object files: ==="
	$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo  "=== Compiling $<: ==="
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "=== Removing .o files and bin ==="
	@rm -f $(OBJDIR)/*.o 
	@rm sl