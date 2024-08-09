/*  readRecord.c -- Read a record from the credit registery */

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

void readRecord(FILE *fPtr) {
  clientData client = {0, "", "", 0.0};

  if ((fPtr = fopen("credit.dat", "r")) == NULL) {
    printf("Could not read accounts database\n");
  } else {
    rewind(fPtr);
    printf("%-6s%-16s%-11s%10s\n", "Acct", "First Name", "Last Name",
           "Balance");

    while (!feof(fPtr)) {
      fread(&client, sizeof(clientData), 1, fPtr);

      if (client.acctNum != 0) {
        printf("%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastName,
               client.firstName, client.balance);
      }
    }

    fclose(fPtr);
  }
}
