/*  newRecord.c -- Allocate a new record in the credit registery */

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

void newRecord(FILE *fPtr) {

  clientData client = {0, "", "", 0.0};

  int accountNum;

  printf("Enter new account number ( 1 - 100 ): ");
  scanf("%d", &accountNum);

  fseek(fPtr, (accountNum - 1) * sizeof(clientData), SEEK_SET);

  fread(&client, sizeof(clientData), 1, fPtr);

  if (client.acctNum != 0) {
    printf("Account #%d already contains information.\n", client.acctNum);
  } else {

    printf("Enter lastname, firstname, balance\n/ ");
    scanf("%s%s%lf", &client.lastName, &client.firstName, &client.balance);

    client.acctNum = accountNum;

    fseek(fPtr, (client.acctNum - 1) * sizeof(clientData), SEEK_SET);

    fwrite(&client, sizeof(clientData), 1, fPtr);
  }
}
