# Project Name and Directories
TARGET_NAME = vnav_efcs
SRCDIR      = src
INCDIR      = include
OBJDIR      = obj
BINDIR      = bin

# Compiler and Flags
CC          = gcc
# -Wall -Wextra: Show all helpful warnings
# -I$(INCDIR): Look for .h files in the include directory
CFLAGS      = -Wall -Wextra -I$(INCDIR)

# Logic to find all .c files in src/ and define corresponding .o files in obj/
SRCS        = $(wildcard $(SRCDIR)/*.c)
OBJS        = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET      = $(BINDIR)/$(TARGET_NAME)

# Default rule: Build the final binary
all: $(TARGET)

# Linker Stage: Combine object files into the final executable
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJS) -o $(TARGET)
	@echo "Build Successful: $(TARGET)"

# Compilation Stage: Compile each .c file into a .o file
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Stage: Remove build artifacts
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	@echo "Project cleaned."