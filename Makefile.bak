# Directories
srcdir       := src
testdir      := test
VPATH        := $(srcdir) $(testdir)

# Files
sources      := ${wildcard $(srcdir)/*.cpp}
headers      := ${subst .cpp,.hpp,$(sources)}
objects      := ${subst .cpp,.o,$(sources)}
cases        := ${wildcard $(testdir)/*.cxx}
tests        := ${subst .cxx,,$(cases)}
depends      := ${subst .hpp,.d,$(headers)} ${subst .cxx,.d,$(cases)}

# Flags
CXX          := g++
INCLUDES     := -Isrc -Itest
CXXFLAGS     := -g $(INCLUDES)
LIBS         := -lX11 -lXi -lXmu -lGL
LDFLAGS      := $(LIBS)

# Interface
.PHONY: all clean
.DEFAULT: all
all: tests objects
clean:
	$(RM) $(objects)
	$(RM) $(depends)
	$(RM) $(tests)

# Objects
.PHONY: objects
objects: ${notdir $(objects)}
%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Tests
.PHONY: tests
tests: ${notdir $(tests)}
%: %.cxx
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(testdir)/$@

# Dependencies
.PHONY: depends
depends: $(depends)
%.d: %.hpp
	$(CXX) $(CXXFLAGS) -MM $< > $@
%.d: %.cxx
	$(CXX) $(CXXFLAGS) -MM $< | sed 's/\.o//;s/\.hpp/\.o/g' > $@
ifneq ($(MAKECMDGOALS),clean)
  -include $(depends)
endif
