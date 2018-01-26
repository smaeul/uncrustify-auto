CPPFLAGS = -D_GNU_SOURCE -D_XOPEN_SOURCE=700 -DALLOW_IGNORE=0
CFLAGS = -O2

# Replace with your own repo (or just put something in ./src)
REPO = git://git.musl-libc.org/musl

all: count permute

clean:
	rm -f count permute options.h

try: count permute | src
	./try.sh $|/src

count: count.c options.h types.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -std=c11 -o $@ $<

permute: permute.c options.h types.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -std=c11 -o $@ $<

options.h:
	uncrustify --show-config | grep '^[[:alpha:]]' | sed \
		-e 's/{ Auto, LF, CR, CRLF }/LineEnding/' \
		-e 's/{ False, True }/Boolean/' \
		-e 's/{ Ignore, Add, Remove, Force }/IgnoreAddRemoveForce/' \
		-e 's/{ Ignore, Lead, Trail }/IgnoreLeadTrail/' \
		-e 's/Unsigned Number/UnsignedNumber/' \
		-e 's/^\([[:graph:]]\+\)\s\+\([[:graph:]]\+\)$$/\t{ .name = "\1", .type = \&\2 },/' \
		> $@

src:
	git clone $(REPO) $@

.PHONY: all clean try
