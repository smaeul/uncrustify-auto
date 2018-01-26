/*
 * Copyright © 2017 Samuel Holland <samuel@sholland.org>
 * SPDX-License-Identifier: 0BSD
 */

struct type {
	bool keep;
	unsigned int nvalues;
	char *values[];
};

struct type Boolean = {
	.keep = true,
	.nvalues = 2,
	.values = { "False", "True" },
};

struct type IgnoreAddRemoveForce = {
	.keep = true,
#if ALLOW_IGNORE
	.nvalues = 4,
	.values = { "Ignore", "Add", "Remove", "Force" },
#else
	.nvalues = 3,
	.values = { "Add", "Remove", "Force" },
#endif
};

struct type IgnoreLeadTrail = {
	.keep = true,
#if ALLOW_IGNORE
	.nvalues = 3,
	.values = { "Ignore", "Lead", "Trail" },
#else
	.nvalues = 2,
	.values = { "Lead", "Trail" },
#endif
};

struct type LineEnding = {
	.keep = true,
#if ALLOW_IGNORE
	.nvalues = 4,
	.values = { "Auto", "LF", "CR", "CRLF" },
#else
	.nvalues = 3,
	.values = { "LF", "CR", "CRLF" },
#endif
};

struct type Number = {
	.keep = true,
	.nvalues = 5,
	.values = { "0", "1", "2", "4", "8" },
};

struct type String = {
	.keep = false,
};

struct type UnsignedNumber = {
	.keep = true,
	.nvalues = 5,
	.values = { "0", "1", "2", "4", "8" },
};
