// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// Ayisha Sameera,GET.
// ------------------------------------------------------------------
// Test.c
// Program on branch B10.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//Color codes.
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

typedef enum {
   MinLength,
   MaxLength,
   SpChar,
   Digit,
   Upper,
   Lower
}Error;

// Checks the validity of the password.
void CheckPassword (char* str, bool* error);

void CheckPassword (char* str, bool* error) {
   size_t length = strlen (str);
   if (length >= 7) error[MinLength] = true;  // Within minimum length.
   if (length <= 16) error[MaxLength] = true; // Within maximum length.
   if (strpbrk ("!@#$%^&*()-+", str) != NULL) error[SpChar] = true; // Has a special character.
   for (int i = 0; i < length && !(error[Lower] && error[Upper] && error[Digit]); i++) {
      if (islower (str[i])) error[Lower] = true;// Has a lowercase character.
      else if (isupper (str[i])) error[Upper] = true; // Has an uppercase character.
      else if (isdigit (str[i])) error[Digit] = true; // Has a digit.
   }
}

static void PrintResult (bool* error) {
   char* message[6] = { "Password requires atleast 6 characters\n",
                        "Password should not exceed 15 characters\n",
                        "Password should have atleast one special character\n",
                        "Password should have atleast one numeric character\n",
                        "Password should have atleast one uppercase character\n",
                        "Password should have atleast one lowercase character\n" };
   bool isPass = true;
   for (int i = 0; i < 6; i++) {
      printf (RED"%s"RESET, !error[i] ? message[i] : "");
      isPass *= error[i];
   }
   if (isPass) printf (GREEN"Password is strong\n"RESET);
   else if (!(error[SpChar] && error[Lower] && error[Upper] && error[Digit]))
      printf (YELLOW"Password is weak\n"RESET);
}

int main () {
   do {
      char input[20];
      printf ("Enter \"EXIT\" to exit\nEnter password : ");
      fgets (input, sizeof (input), stdin);
      if (input[strlen (input) - 1] != '\n') while (getchar () != '\n');
      if (!strcmp ("EXIT\n", input)) break;
      // Assume the password is incorrect.
      bool error[6] = { false,false,false,false,false,false };
      CheckPassword (input, error);
      PrintResult (error);
   } while (true);
}