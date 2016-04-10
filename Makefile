DEPFLAGS = -MT $@ -MMD -MP -MF $*.Td

CPPFLAGS = -std=c++0x -stdlib=libc++ -g3 -Wall -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lSDL2

TARGET_ARCH = -arch x86_64

SRCS = $(wildcard src/*.cc)
OBJS = $(patsubst %.cc,%.o,$(SRCS))
EXEC = tinyrenderer

$(EXEC): $(OBJS)
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH) -o $@ $^

# Automatic dependency tracking solution taken from
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
# TODO(jlfwong): Go re-read that article, I don't understand why the %.d:
# ; dummy rule is needed or why %.d needs to be one of the depdendences of %.o

%.o: %.cc
%.o: %.cc %.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -o $@ -c $<
	mv -f $*.Td $*.d

%.d: ;

clean:
	rm -f $(EXEC) src/*.o src/*.d

.PRECIOUS: %.d
.PHONY: clean

-include $(patsubst %,%.d,$(SRCS))
