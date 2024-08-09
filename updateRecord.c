/*  updateRecord.c -- Update clients' credits in the credit registery */

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

void updateRecord(FILE *fPtr) {
  int account;
  double transaction;

  clientData client = {0, "", "", 0.0};

  printf("Enter account to update ( 1 - 100 ): ");
  scanf("%d", &account);

  fseek(fPtr, (account - 1) * sizeof(clientData), SEEK_SET);

  fread(&client, sizeof(clientData), 1, fPtr);

  if (client.acctNum == 0) {
    printf("Account #%d has no information.\n", account);
  } else {
    printf("%-6d%-16s%-11s%10.2f\n\n", client.acctNum, client.lastName,
           client.firstName, client.balance);

    printf("Enter charge ( + ) or payment ( - ): ");
    scanf("%lf", &transaction);
    client.balance += transaction;

    printf("%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastName,
           client.firstName, client.balance);

    fseek(fPtr, (account - 1) * sizeof(clientData), SEEK_SET);

    fwrite(&client, sizeof(clientData), 1, fPtr);
  }
}
