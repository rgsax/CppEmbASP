CXX = g++
EMBASP_FLAGS = -std=c++17 -pthread -lboost_system -lboost_filesystem

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(EMBASP_FLAGS)

program: $(obj)
	$(CXX) -o $@  $^ $(EMBASP_FLAGS) 

.PHONY: clean
clean:
	rm -f $(obj) program

