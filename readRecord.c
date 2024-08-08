#ifndef GNUBANK_H
#include "gnubank.h"
#endif

void
readRecord(FILE *fPtr)
{
  clientData client = { 0, "", "", 0.0 };

  if (( fPtr = fopen("credit.dat", "r" )) == NULL )
  {
    printf("Could not read accounts database\n");
  }
  else
  {
    rewind( fPtr );
    printf( "%-6s%-16s%-11s%10s\n",
	  "Acct", "First Name", "Last Name", "Balance" );

    while (!feof( fPtr ) )
    {
      fread( &client, sizeof( clientData ), 1, fPtr);

      if ( client.acctNum != 0 )
      {
	      printf( "%-6d%-16s%-11s%10.2f\n",
	      client.acctNum, client.lastName,
	      client.firstName, client.balance );
      }
    }

    fclose( fPtr );
  }
  
}

