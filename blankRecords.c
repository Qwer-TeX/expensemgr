/*  blankRecords.c -- Allocate 100 blank records to the credit registery */

/*  Copyright (c) 2024 Robert Johnson. All Rights Reserved.
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
#include "gnubank.h"
#endif

void blankRecords(FILE *fPtr) {
  clientData blankClient = {0, "", "", 0.0};

  for (int i = 1; i <= 100; i++) {
    fwrite(&blankClient, sizeof(clientData), 1, fPtr);
  }

  fclose(fPtr);
}
