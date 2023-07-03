#include <fcntl.h>
#define main main1
#include "main.c"

#undef main

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

FILE *f;
char text[200] = "";

void create_test_values()
{
  f = fopen("in", "w");
  fputs("5, 6", f);
  fclose(f);
}

void setup_test()
{
  // put test values into "in" file.
  create_test_values();

  // use file input to mock stdin
  f = freopen("in", "r", stdin);
  if (f == NULL)
  {
    printf("failed to open file\n");
  }

  // redirect stdout to "file", and save stdout
  int out = open("output", O_WRONLY | O_CREAT | O_TRUNC, 0777);
  int saved = dup(1);

  close(1);
  dup(out);
  close(out);

  main1();

  fflush(stdout);
  // restore stdout and close the files
  dup2(saved, 1);
  close(saved);
  fclose(f);
}

void append(char *s, char c)
{
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
}

char *get_result()
{
  // open file
  FILE *textfile;
  textfile = fopen("output", "r");

  // check if there has been messages on the terminal.
  if (textfile == NULL)
  {
    printf("\nNo messages printed to the terminal!\n");
  }

  rewind(textfile);

  // read file char by char until EOF
  char ch;
  while (1)
  {
    ch = fgetc(textfile);
    if (ch == EOF)
      break;
    append(text, ch);
  }
  fclose(textfile);

  return text;
}

void area_test()
{
  CU_ASSERT_TRUE(strstr(text, "30") != NULL);
}

void perimeter_test()
{
  CU_ASSERT_TRUE(strstr(text, "22") != NULL);
}

int init_suite()
{
  setup_test();
  get_result();

  return 0;
}

int cleanup_suite()
{
  // delete temporary files
  if (remove("in") == 0 && remove("output") == 0)
    return 0;
}

int main()
{
  CU_initialize_registry();
  CU_pSuite suite = CU_add_suite("Teglalap_test", init_suite, cleanup_suite);
  CU_add_test(suite, "Area test", area_test);
  CU_add_test(suite, "Perimeter test", perimeter_test);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
