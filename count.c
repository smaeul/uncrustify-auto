/*
 * Copyright © 2017 Samuel Holland <samuel@sholland.org>
 * SPDX-License-Identifier: 0BSD
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

int
main(int argc, char *argv[])
{
	char *delim, *line = NULL, *name, *value;
	size_t size = 0;
	ssize_t len;

	if (argc != 2) {
		fprintf(stderr, "You must specify an option!\n");
		return 1;
	}

	if (strstr(argv[1], "_width"))
		goto fail;
	if (!strcmp(argv[1], "indent_ternary_operator"))
		goto fail;
	if (!strcmp(argv[1], "nl_multi_line_define"))
		goto fail;

	for (int i = 0; i < ARRAY_SIZE(options); ++i) {
		if (!strcmp(argv[1], options[i].name)) {
			printf("%d\n", options[i].type->nvalues);
			return 0;
		}
	}

fail:
	printf("%d\n", 0);
	return 0;
}
