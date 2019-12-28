# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# https://www.tutorialspoint.com/makefile/makefile_macros.htm
# The make program allows you to use macros, which are similar to variables. Macros are defined in a Makefile as = pairs. An example has been shown below −
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/* tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libYOUR_LIBRARY.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
# When one phony target is a prerequisite of another, it serves as a subroutine of the 
# other. For example, here ‘make cleanall’ will delete the object files, the difference files
# , and the file program:
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

# Before issuing any command in a target rule set, there are certain special macros predefined −
# $@ is the name of the file to be made.
# $? is the names of the changed dependents.
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@
$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

#The Unit Tests
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
# Once this is done, ‘make clean’ will run the recipe regardless of whether there is 
# a file named clean.
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

# The Cleaner
# In this example, the clean target will not work properly if a file named clean is 
# ever created in this directory. Since it has no prerequisites, clean would always be 
# considered up to date and its recipe would not be executed. To avoid this problem you 
# can explicitly declare the target to be phony by making it a prerequisite of the special 
# target .PHONY
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf 'find . -name "*.dSYM" -print'

# The Install
# target [target...] : [dependent ....]
# [ command ...]
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
check:
	@echo Files with potentially dangerous functions.
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		|stpn?cpy|a?sn?printf|byte_)' $(SOURCES) || true
