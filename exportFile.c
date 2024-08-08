/*  exportFile.c -- Export the credit registery as a readable file in multiple amount of formats */

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
exportFile( FILE *readPtr )
{
  FILE *writePtr;

  clientData client = { 0, "", "", 0.0 };

  if ( ( writePtr = fopen( "accounts.txt", "w" ) ) == NULL )
  {
    printf("accounts.txt cannot be created\n");
  }
  else
  {
    rewind( readPtr );
    fprintf( writePtr, "%-6s%-16s%-11s%10s\n",
	  "Acct", "Last Name", "First Name", "Balance" );


    while (!feof( readPtr ) )
    {
      fread( &client, sizeof( clientData ), 1, readPtr );

      if ( client.acctNum != 0 )
      {
	      fprintf( writePtr, "%-6d%-16s%-11s%10.2f\n",
	                  client.acctNum, client.lastName,
	                 client.firstName, client.balance );
      }

    }

    fclose( writePtr );
  }

}
