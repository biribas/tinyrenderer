SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

BUILDDIR = build
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

TARGETDIR = bin
TARGET = tiny

FLAGS = -Wall -Wextra -pedantic -I./include

$(TARGET): $(OBJECTS)
	@echo "Linking files..."
	@mkdir -p $(TARGETDIR)
	@g++ $(FLAGS) $(OBJECTS) -o $(TARGETDIR)/$(TARGET)
	@echo "Done!"

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Building $<"
	@mkdir -p $(BUILDDIR)
	@g++ -c $(FLAGS) $< -o $@

clean:
	@$(RM) -rfv $(BUILDDIR) $(TARGETDIR)