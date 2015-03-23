SRCS = ilda.cpp main.cpp

FLAGS = -F/Library/Frameworks -framework SDL2 -framework Cocoa -framework OpenGL

iview: $(SRCS)
	$(CXX) -std=c++1y $(SRCS) -I../src -Wall $(FLAGS) -o $@

clean:
	rm -f iview
