/*  gnubank.h -- Function declarations and data structure initializations */

/*  Copyright (C) 2024  Mitnew
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GNUBANK_H
#define GNUBANK_H

/* #define DEBUG */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#define FREE(p)   do { free (p); (p) = NULL; } while(0)

void print_usage( FILE *strm, int exit_code );
void print_license();
void mkdatafile();
int enterChoice();
void readRecord( FILE *fPtr );
void exportFile( FILE *readPtr );
void importFile( FILE *readPtr );
void updateRecord( FILE *fPtr );
void newRecord( FILE *fPtr );
void deleteRecord( FILE *fPtr );
void blankRecords( FILE *fPtr );

typedef struct
clientData {
  int acctNum;
  char lastName[ 15 ];
  char firstName[ 10 ];
  double balance;
} clientData;

#endif /* GNUBANK_H */
