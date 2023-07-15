SRCS := $(wildcard ./*.cpp)
OBJS := $(patsubst ./%.cpp, $(TARGET)/%.o,$(SRCS))

all: $(TARGET) $(OBJS) $(TARGET)/libHyperDesigner.a

clean:
	$(RM) $(TARGET)

# Ensure output directory is built
$(TARGET):
	mkdir $(TARGET)

$(TARGET)/%.o: ./%.cpp 
	$(GCC) $(CFLAGS) -c -o $@ $^ $(INCLUDE)

# Make .a file
$(TARGET)/libHyperDesigner.a: $(OBJS)
	ar rvs $@ $^
