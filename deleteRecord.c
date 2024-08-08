/*  blankRecords.c -- Delete a record from the credit registery */

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
#include "gnubank.h"
#endif

void
deleteRecord( FILE *fPtr )
{

  clientData client;
  clientData blankClient = { 0, "", "", 0 };

  int accountNum;

  printf( "Enter account number to delete ( 1 - 100 ): " );
  scanf( "%d", &accountNum );

  fseek( fPtr, ( accountNum - 1 ) * sizeof ( clientData ),
      SEEK_SET );

  fread( &client, sizeof ( clientData ), 1, fPtr );

  if ( client.acctNum == 0 ) {
    printf( "Account %d does not exist.\n", accountNum );
  }
  else {

    fseek( fPtr, ( accountNum - 1 ) * sizeof ( clientData ),
	SEEK_SET );

    fwrite( &blankClient,
	sizeof( clientData ), 1, fPtr );
  }

}

