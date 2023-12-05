CXX = g++-11 -std=c++20
CXXFLAGS = -Wall -g -MMD -Werror=vla # use -MMD to generate dependencies
SOURCES = $(filter-out graphicsdisplay.cc window.cc, $(wildcard *.cc))
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chess

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)
	strip $(EXEC)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)
