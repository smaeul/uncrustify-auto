/*
 * permute.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

struct {
	char *name;
	struct type *type;
} options[] = {
#include "options.h"
};

char *
next(struct type *type, char *value)
{
	int idx = 0;

	for (int i = 0; i < type->nvalues; ++i) {
		if (!strcasecmp(type->values[i], value)) {
			idx = (i + 1) % type->nvalues;
			break;
		}
	}

	return type->values[idx];
}

int
main(int argc, char *argv[])
{
	char *delim, *line = NULL, *name, *value;
	size_t size = 0;
	ssize_t len;

	if (argc != 2) {
		fprintf(stderr, "You must specify an option to change!\n");
		return 1;
	}

	while ((len = getline(&line, &size, stdin)) > 0) {
		delim = strchr(line, '=');
		if (!delim || strncmp(line, argv[1], delim - line)) {
			printf("%s", line);
			continue;
		}

		/* Remove newline */
		line[len - 1] = '\0';

		/* Split name/value */
		*delim = '\0';
		name = line;
		value = delim + 1;

		for (int i = 0; i < ARRAY_SIZE(options); ++i) {
			if (!strcmp(name, options[i].name)) {
				value = next(options[i].type, value);
				break;
			}
		}

		printf("%s=%s\n", name, value);
	}
}
