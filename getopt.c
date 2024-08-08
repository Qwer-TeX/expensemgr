/*
 * Copyright (c) 1987 University of Maryland Department of Computer Science.
 * All rights reserved.  Permission to copy for any purpose is hereby granted
 * so long as this copyright notice remains intact.
 */

/*
 * getopt - get option letter from argv
 * (From Henry Spencer @ U of Toronto Zoology, slightly edited)
 *
 * Modernized by Robert Johnson <mitnew842 AT gmail dot com>
 */

#include <stdio.h>
#include <string.h>

char *optarg; /* Global argument pointer. */
int optind;   /* Global argv index. */

static char *scan; /* Private scan pointer. */

extern char *index();

int getopt(int argc, char **argv, char *optstring) {
  int c;
  char *place;

  optarg = NULL;
  if (scan == NULL || *scan == 0) {
    if (optind == 0)
      optind++;
    if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == 0)
      return (EOF);
    if (strcmp(argv[optind], "--") == 0) {
      optind++;
      return (EOF);
    }
    scan = argv[optind] + 1;
    optind++;
  }
  c = *scan++;
  place = index(optstring, c);

  if (place == NULL || c == ':') {
    fprintf(stderr, "%s: unknown option -%c\n", argv[0], c);
    return ('?');
  }
  place++;
  if (*place == ':') {
    if (*scan != '\0') {
      optarg = scan;
      scan = NULL;
    } else {
      if (optind >= argc) {
        fprintf(stderr, "%s: missing argument after -%c\n", argv[0], c);
        return ('?');
      }
      optarg = argv[optind];
      optind++;
    }
  }
  return (c);
}
