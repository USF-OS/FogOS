#include "shuf.h"
#include "user.h"
#include "../kernel/fcntl.h"

int seedflag = 0;


void arg_error(char* error)
{
  printf("shuf: %s\n", error);
  exit(-1);
}

void parse_file(config_t* cp, vec_t *vec) 
{
  uint sz = 0;
  char *line = NULL;
  int fd = open(cp->input, O_RDONLY);
  if (fd == -1) arg_error("Input file doesn't exist");
  while (1) {
    if (getline(&line, &sz, fd) <= 0) {
      break;
	}
    vec_push(vec, line);
  }
  free(line);
}

void update_file(config_t* cp, char* fn, int option)
{
  int len = strlen(fn);
  if (len > FILE_NAME_LEN - 1) {
    arg_error("Output file name too long");
  }
  switch (option) {
    case 1:
      strcpy(cp->input, fn);
      break;
    case 2:
      strcpy(cp->output, fn);
      break;
    default:
      arg_error("Improper use of update_file function");
  }
}

void update_lines_printed(config_t* cp, int n)
{
  cp->num_lines = n;
}

void parse_input(int argc, char** argv, config_t* cp)
{
  int i = 1;
  while (i < argc) {
   
    if (strcmp(argv[i], "-o") == 0) {
      if (argv[++i] == NULL) {
         arg_error("No file present after -o flag");
      }
      update_file(cp, argv[i], 2);
    } else if (strcmp(argv[i], "-n") == 0) {;
      if (argv[++i] == NULL) {
        arg_error("No line count present after -n flag");
      }
      int n = atoi(argv[i]);
      if (n <= 0) arg_error("Requesting 0 or less lines in output");
      update_lines_printed(cp, n);
    } else if (strcmp(argv[i], "-h") == 0) {
      printf("Usage: shuf \"file name\" *required*\nAdditional flags:\n-n \"# of lines to output\"\n-o \"file name to output to\"\n-t \"set seed for tests\"\n");
      exit(0);
    } else if (strcmp(argv[i], "-t") == 0) {
      if (argv[++i] == NULL) {
        arg_error("No seed given after -t flag");
      }
      seedflag = atoi(argv[i]);
    } else {
      if (argv[i][0] == '-'){
      	  arg_error("Invalid flag");
      }
      if (strlen(cp->input) != 0) {
      	arg_error("Too many files: possibly missing flag for output file");
      }
	  update_file(cp, argv[i], 1);
    }  
    i++;
  }
  if (strlen(cp->input) == 0) {
    arg_error("No input file found");
  }
}

void handle_output(config_t* cp, vec_t* vec)
{
  fisher_yates(vec, seedflag);
  // handler for no output file, print to stdout
  if (strlen(cp->output) == 0) {
    // handler for num_lines to output
    switch (cp->num_lines) {
      case -1:
        for (int i = 0; i < vec->len; i++) {
          printf("%s", vec->strings[i]);
        }
        break;
      default:
        if (cp->num_lines >= vec->len) arg_error("Requesting more lines printed than found in file");
        for (int i = 0; i < cp->num_lines; i++) {
          printf("%s", vec->strings[i]);
        }
        break;
    }
  } else {
    int fd = open(cp->output, O_CREATE | O_RDWR);
    if (fd == -1) arg_error("Output file doesn't exist");
    switch (cp->num_lines) {
      case -1:
        for (int i = 0; i < vec->len; i++) {
          fprintf(fd, "%s", vec->strings[i]);
        }
        break;
      default:
        if (cp->num_lines >= vec->len) arg_error("Requesting more lines printed than found in file");
        for (int i = 0; i < cp->num_lines; i++) {
          fprintf(fd, "%s", vec->strings[i]);
        }
        break;
    }
  }
  return;
}

void shuf_start(int argc, char** argv)
{
  vec_t vec;
  vec_init(&vec, 5);
  config_t config = {"", "", -1};
  
  parse_input(argc, argv, &config);
  parse_file(&config, &vec);
  handle_output(&config, &vec);
}
