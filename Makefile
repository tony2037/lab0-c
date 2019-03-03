CC = gcc
CFLAGS = -O0 -g -Wall -Werror

TESTS = \
	merge_sort

TESTS := $(addprefix tests/,$(TESTS))

GIT_HOOKS := .git/hooks/applied
all: $(GIT_HOOKS) qtest

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

queue.o: queue.c queue.h harness.h
	$(CC) $(CFLAGS) -c queue.c 

qtest: qtest.c report.c console.c harness.c queue.o
	$(CC) $(CFLAGS) -o qtest qtest.c report.c console.c harness.c queue.o

test: qtest scripts/driver.py
	scripts/driver.py

$(TESTS): $(TESTS).c report.c console.c harness.c queue.o
	$(CC) $(CFLAGS) -I./ -o $@ $< report.c console.c harness.c queue.o

clean:
	rm -f *.o *~ qtest 
	rm -rf *.dSYM
	(cd traces; rm -f *~)

