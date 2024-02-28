#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


struct dateTime
{
  uint64 secs;
  uint64 minutes;
  uint64 hours;
  uint64 days;
  uint64 years;

  // Indexing a char array of day names
  int curr_day_index;
  // Indexing a char array of month names
  int curr_month_index;

  char *name_of_day;
  char *name_of_month;
};


// Returning dateTime struct by setting metrics(secs, minutes, hours, etc) 
// to current totals.
// years is excluded because of leap year math
struct dateTime*
set_Epoch(uint64 s)
{
  struct dateTime *ep = (struct dateTime*)malloc(sizeof(struct dateTime));
  ep->secs = s;
  ep->minutes = s / 60;
  ep->hours = ep->minutes / 60;
  ep->days = ep->hours / 24;
  ep->years = 0;

  // day 0 indexes to Thu in char array
  ep->curr_day_index = 0;
  ep->curr_month_index = 0;

  return ep;
}

/*                          ~ set_dateTime ~
* using epoch and unix timestamp to calculate a dateTime struct based on current 
* time
*  
* epoch: (struct dateTime) dateTime pointer that points to struct information 
*        based on time at Epoch (Thu 1st Jan 1970)
*
* return: struct dateTime of current information
*/
struct dateTime*
set_dateTime(struct dateTime *epoch)
{
  struct dateTime *current = (struct dateTime*)malloc(sizeof(struct dateTime));
  
  // Calculate which day it is
  char *days[] = {"Thu", "Fri", "Sat", "Sun", "Mon", "Tue", "Wed"};
  current->curr_day_index = (epoch->days % 7) - 1;
  current->name_of_day = days[((epoch->days % 7) - 1)];

  // Array of days in each month (Jan - Dec)
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
                    "Sep", "Oct", "Nov", "Dec"};

  // Days left from epoch
  int days_left = epoch->days;

  // While loop increments at the start
  // so we start at 1970
  int years = 1969;

  // keeps track of month thru iteration
  int month_idx = 0;

  while (days_left > 0)
  {

    years++;

    // Checks if leap year
    if ((years % 4 == 0 && years % 100 != 0) || years % 400 == 0) {
      days_in_month[1] = 29;
    } else {
      days_in_month[1] = 28;
    }

    // Iterates through the days_in_month array and decrements from days
    // since epoch to ensure leap years are accounted for, thus, increasing
    // accuracy of days since epoch
    for (month_idx = 0; month_idx < 12; month_idx++)
    {
      days_left -= days_in_month[month_idx];

      if (days_left < 0) {
        break;
      }
    }
  } // end while loop

  current->curr_month_index = month_idx + 1;
  current->name_of_month = months[month_idx];
  current->days = days_in_month[month_idx] + days_left;
  current->years = years;

  // Calculate time (HH:MM:SS format)
  current->secs = epoch->secs % 60;
  current->minutes = (int)(epoch->secs / 60) % 60;
  current->hours = ((epoch->secs / 60 / 60) % 24) - 8;


  return current;
}

/*                            ~ parse_args ~
* takes command line arguments and configures output to stdout. Formatting options
* are taken into account and various other options taken from man pages
*
* dt:  (dateTime*) holds current dateTime information
* argc:(int) amount of command line arguments there are
* argv:(char**) command line arguments as an array of char*
*/

void
parse_args(struct dateTime *dt, int argc, char **argv)
{

  if (argc < 2) {
    printf("%d/%d/%d\n", dt->curr_month_index, dt->days, dt->years);
  }
  else if (argc >= 2) {

    if (strstr(argv[1], "--date") == 1 || strstr(argv[1], "-F") == 1) {

      for (int i = 1; i < argc; i++) {
        
        // Format name of today
        if (strstr(argv[i], "%a") == 1) {
          printf("%s ", dt->name_of_day);

        // Format this month's name
        } else if (strstr(argv[i], "%b") == 1) {
          printf("%s ", dt->name_of_month);

        // Format full date
        } else if (strstr(argv[i], "%c") == 1) {
          printf("%s %s %d ", dt->name_of_day, dt->name_of_month, dt->days);
          printf("%d:%d:%d %d ", dt->hours, dt->minutes, dt->secs, dt->years);

        // Format current year
        } else if (strstr(argv[i], "%Y") == 1) {
          printf("%d ", dt->years);
        }

        // Format alphabetic time zone abbreviation
        else if (strstr(argv[i], "%Z") == 1) {
          printf("PST ");
        }

        // Format current date
        else if (strstr(argv[i], "%x") == 1) {
          printf("%d/%d/%d ", dt->curr_month_index, dt->days, dt->years);
        }

        // Format time now
        else if (strstr(argv[i], "%X") == 1) {
          printf("%d:%d:%d ", dt->hours, dt->minutes, dt->secs);
        }

        // Add new line
        else if (strstr(argv[i], "%n") == 1) {
          printf("\n");
        }

        // Add tab space
        else if (strstr(argv[i], "%t") == 1) {
          printf("\t");
        }
      }
      printf("\n");
    } else {
      // Output date and time in RFC 5322 format
      if (strcmp(argv[1], "-R") == 0 || strcmp(argv[1], "--rfc-email") == 0) {
      printf("%s, %d %s %d ", dt->name_of_day, dt->days, dt->name_of_month, dt->years);
      printf("%d:%d:%d +0800\n", dt->hours, dt->minutes, dt->secs);
      }

      // Output UTC
      else if (strcmp(argv[1], "--utc") == 0 || strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "--universal") == 0) {
        printf("%d:%d:%d UTC\n", dt->hours + 8, dt->minutes, dt->secs);
      }

      // Output help information
      else if (strcmp(argv[1], "--help") == 0) {
        printf("\n-d, -F=STRING, --date=STRING\n\tdisplay time described by STRING, not 'now'\n\n");
        printf("-R, --rfc-email\n\toutput date and time in RFC 5322 format.Example: Mon, 14\n\tAug 2006 02:34:56 -0600\n");
        printf("-u, --utc, --universal\n\tprint or set Coordinated Universal Time (UTC)\n");
        printf("--help display this help and exit\n");
        printf("\nFormat options:\n");
        printf("%a     locale's abbreviated weekday name (e.g., Sun)\n");
        printf("%b     locale's abbreviated month name (e.g., Jan)\n");
        printf("%c     locale's date and time (e.g., Thu Mar  3 23:05:25 2005)\n");
        printf("%Y     year\n");
        printf("\%x     locale's date representation (e.g., 12/31/99)\n");
        printf("%X     locale's time representation (e.g., 23:13:48)\n");
        printf("%t     a tab\n");
        printf("%n     a newline\n");
      }
    }
  }
}

int
main(int argc, char *argv[])
{
  struct dateTime *epoch = set_Epoch(clock() / 1000000000);
  struct dateTime *current = set_dateTime(epoch);

  parse_args(current, argc, argv);

  return 0;
}
