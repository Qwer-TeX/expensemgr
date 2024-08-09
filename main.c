/*  main.c -- The main function implementation */

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

int verbose;

int isverbose() {
  int verbose;
  if (verbose == 1)
    return 1;
  else
    return 0;
}

int main(int argc, char *argv[]) {
  FILE *cFPtr;
  int choice;
  int next_opt;

  while ((cFPtr = fopen("credit.dat", "rb+")) == NULL) {
    mkdatafile();
  }

  const char *const short_options = "ho:vpPl";
  const struct option long_options[] = {
      {"help", 0, NULL, 'h'},    {"output", 1, NULL, 'o'},
      {"verbose", 0, NULL, 'v'}, {"print", 0, NULL, 'p'},
      {"prompt", 0, NULL, 'P'},  {"license", 0, NULL, 'l'},
      {NULL, 0, NULL, 0}};

  const char *output_filename = NULL;
  extern int verbose;
  verbose = 0;

  const char *program_name = argv[0];

  if (argc == 1) {
#ifdef DEBUG
    while ((choice = enterChoice()) != 8) {
#endif
#ifndef DEBUG
    TOGGLE:
      while ((choice = enterChoice()) != 8) {
#endif
        switch (choice) {

        case 1:
          readRecord(cFPtr);
          break;

        case 2:
          exportFile(cFPtr);
          break;

        case 3:
          importFile(cFPtr);
          break;

        case 4:
          updateRecord(cFPtr);
          break;

        case 5:
          newRecord(cFPtr);
          break;

        case 6:
          deleteRecord(cFPtr);
          break;

        case 7:
          print_license();
          break;

        case 8:
          fprintf(stdout, "bye!");
          break;

        case '*':
        default:
          printf("Incorrect selection\n");
          exit(0);
        }
      }

      fclose(cFPtr);
      exit(1);
    }
    else {
      do {
        next_opt = getopt_long(argc, argv, short_options, long_options, NULL);
        switch (next_opt) {
        case 'h':
          print_usage(stdout, 0);

        case 'o':
          output_filename = optarg;
          break;

        case 'v':
          verbose = 1;
          break;
        case 'p':
          readRecord(cFPtr);
          break;

        case 'P':
#ifdef DEBUG
          printf("Function cannot be implemented because DEBUG is defined\n");
#endif
#ifndef DEBUG
          goto TOGGLE;
#endif
          break;

        case 'l':
          print_license();
          break;

        case '?':
          print_usage(stderr, 1);

        case -1:
          break;

        default:
          abort();
        }

      } while (next_opt != -1);
    }

    if (verbose == 1) {
      printf("Verbose mode specified\n");
    }
  }

  int enterChoice() {
    int menuChoice;

    fprintf(stdout,
            "\n"
            "Expensemgr version %0.1f, Copyright (C) 2024 Mitnew\n"
            "Expensemgr comes with ABSOLUTELY NO WARRANTY\n"
            "This is free software, and you are welcome to redistribute it\n"
            "under certain conditions; type `7' for details.\n",
            VERSION);

    fprintf(stdout,
            "\nEnter your choice               \n"
            "1 - print accounts	               \n"
            "2 - export accounts to file       \n"
            "3 - import accounts to db         \n"
            "4 - update an account             \n"
            "5 - add a new account             \n"
            "6 - delete an account             \n"
            "7 - display license               \n"
            "8 - end program                   \n"
            "                                  \n"
            "-- Switches:                      \n"
            " Verbose:              %s         \n"
            "/ ",
            isverbose() == 1 ? "on" : "off");

    scanf("%d", &menuChoice);

    return menuChoice;
  }

  void mkdatafile() {
    FILE *FPtr;
    if ((FPtr = fopen("credit.dat", "rb+")) == NULL) {
      FPtr = fopen("credit.dat", "w+b+");
      if ((FPtr = fopen("credit.dat", "rb+")) == NULL) {
        printf("Error creating accounts database\n");
      } else {
        blankRecords(FPtr);
      }
    }

    fclose(FPtr);
  }

  void print_license() {
    fprintf(stdout,
            "Expensemgr %.1f\n"
            "Copyright (C) 2024 Mitnew\n"
            "	This program is free software; you can redistribute it and/or "
            "modify\n"
            "	it under the terms of the GNU General Public License; either "
            "version\n"
            "	2 of the License, or (at your option) any later version.\n"
            "\n"
            "	This program is distributed in the hope that it will be "
            "useful,\n"
            "	but WITHOUT ANY WARRANTY; without even the implied warranty "
            "of\n"
            "	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
            "	GNU General Public License for more details.\n"
            "\n"
            "	You should have received a copy of the GNU General Public "
            "License\n"
            "	along with this program. If not, write to\n"
            "\n"
            "	   The Free Software Foundation, Inc.\n"
            "	   51 Franklin Street, Fifth Floor\n"
            "	   Boston, MA 02110-1335  USA"
            "\n"
            "\n",
            VERSION);
  }

  void print_usage(FILE * strm, int exit_code) {
    fprintf(strm, "Usage: expensemgr [-hovpPl]\n");
    fprintf(strm, "Manage your money through expensemgr.\n");
    fprintf(strm, "   -h  --help               Display this message\n");
    fprintf(strm, "   -o  --output[=FORMAT]    Output accounts in the "
                  "specified format\n");
    fprintf(strm, "   -v  --verbose            Display verbose output\n");
    fprintf(strm, "   -p  --print              Print accounts database\n");
    fprintf(strm, "   -P  --prompt             Display the menu\n");
    fprintf(strm, "   -l  --license            Display program license\n");
    exit(exit_code);
  }
