#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char* argv[])
{
  //characters used for isspace
  char c = ' ';
  char notspace = 's';
  
  if (!strcmp(argv[1], "usage")) {
  	printf("How to Use Test Program: \n");
  	printf("Type the function name and the following arguments.\n\n");

  	
  	printf("isdigit: ");
  	printf("\"testchar isdigit (char)\"\n\n");

  	printf("isalpha: ");
  	printf("\"testchar isalpha (char)\"\n\n");

    printf("isupper: ");
    printf("\"testchar isupper (char)\"\n\n");

    printf("islower: ");
    printf("\"testchar islower (char)\"\n\n");

    printf("toupper: ");
    printf("\"testchar toupper (char)\"\n\n");

    printf("tolower: ");
    printf("\"testchar tolower (char)\"\n\n");

    printf("ispunct: ");
    printf("\"testchar ispunct (char)\"\n\n");

    printf("isspace: ");
    printf("\"testchar isspace\"\n\n");

    printf("findindexes: ");
    printf("\"testchar findindexes (string) (char)\"\n\n");

    printf("charcount: ");
    printf("\"testchar charcount (string) (char)\"\n\n");  

    printf("strcount: ");
    printf("\"testchar strcount (string) (substring)\"\n\n");  
    
    printf("strpbrk: ");
    printf("\"testchar strpbrk (string) (substring)\"\n\n"); 
  }

  if (!strcmp(argv[1], "isdigit")) {
    c = argv[2][0];
  	printf("func : isdigit / char : %c : %d\n", c, isdigit(c));
  }
  else if (!strcmp(argv[1], "isalpha")) {
    c = argv[2][0];
  	printf("func : isalpha / char : %c : %d\n", c, isalpha(c));
  }
  else if (!strcmp(argv[1], "isupper")) {
    c = argv[2][0];
  	printf("func : isupper / char : %c : %d\n", c, isupper(c));
  }
  else if (!strcmp(argv[1], "islower")) {
    c = argv[2][0];
  	printf("func : islower / char : %c : %d\n", c, islower(c));
  }
  else if (!strcmp(argv[1], "toupper")) {
    c = argv[2][0];
  	printf("func : toupper / char : %c --> %c\n", c, toupper(c));
  }
  else if (!strcmp(argv[1], "tolower")) {
    c = argv[2][0];
  	printf("func : tolower / char : %c --> %c\n", c, tolower(c));
  }
  else if (!strcmp(argv[1], "ispunct")) {
    c = argv[2][0];
  	printf("func : ispunct / char : %c : %d\n", c, ispunct(c));
  }
  else if (!strcmp(argv[1], "isspace")) {
  	printf("func : isspace / char : %c : %d\n", c, isspace(c));
  	printf("func : isspace / char : %c : %d\n", notspace, isspace(notspace));
  }
  else if (!strcmp(argv[1], "findindexes")) {
    char* str = argv[2];
    char c = argv[3][0];
    int count;
    int indexes[strlen(str)];
    findindexes(str, c, indexes, &count);
  	printf("func: findindexes / string : \"%s\" / char '%c' / indexes : ", str, c);
    for (int i = 0; i < count; i++) {
  	  printf("%d ", indexes[i]);
    }
  }
  else if (!strcmp(argv[1], "charcount")) {
    char* str = argv[2];
    char c = argv[3][0];
  	printf("func: charcount / string : \"%s\" / char '%c' / count : %d", str, c, charcount(str, c));
  }
  else if (!strcmp(argv[1], "strpbrk")) {
    char* str = argv[2];
    char* substr = argv[3];
    if (*strpbrk(str, substr) == '\0' ) {
      printf("func: strpbrk / string : \"%s\" / substring %s' / first matching char : %s", str, substr, "NOT FOUND");
    }
    else {
  	  printf("func: strpbrk / string : \"%s\" / substring %s' / first matching char : %c", str, substr, *strpbrk(str, substr));
    }
  }
  else if (!strcmp(argv[1], "strcount")) {
    char* str = argv[2];
    char* substr = argv[3];
  	printf("func: strcount / string : \"%s\" / substring %s' / count : %d", str, substr, strcount(str, substr));
  }
  else{
    printf("A valid function was not chosen.\nPlease use \"testchar usage\" for how to use.\n");
  	return 0;
  }
  return -1;
}
