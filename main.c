#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "string_library.h"

int main()
{
    char s1[] = "aaaaaa", s2[] = "bbbbbbbb";
    int newLength = 2;
    printf("Function Tests:\n");

    printf("\n\tString 1: \"%s\"\tString 2: \"%s\"\n", s1, s2);

    //1. int all_letters
    printf("\n\t1. int all_letters(char* s): %u\n", all_letters(s1));

    //2. int num_in_range
    printf("\t2. int num_in_range(char* s1, char b, char t): %u\n", num_in_range(s1, 'a', 'z'));

    //3. int diff
    printf("\t3. int diff(char* s, int new_len): \"%s\" --> \"%s\"", s1, s2);
    printf(" takes %u steps\n", diff(s1, s2));

    //4. void shorten
    char s4[] = "This string will shorten to 4";
    printf("\t4. void shorten(char* s, int new_len): \"%s\"", s4);
    shorten(s4, 4);
    printf(" --> \"%s\"\n", s4);

    //5. int len_diff
    printf("\t5. int len_diff(char* s1, char* s2): %i\n", len_diff(s1, s2));

    //6. void rm_left_space
    char s5[] = "       No left space123";
    printf("\t6. rm_left_space(char* s): \"%s\"", s5);
    rm_left_space(s5);
    printf(" --> \"%s\"\n", s5);

    //7. void rm_right_space
    char s6[] = "No right space       ";
    printf("\t7. rm_right_space(char* s): \"%s\"", s6);
    rm_right_space(s6);
    printf(" --> \"%s\"\n", s6);

    //8. void rm_space
    char s7[] = "       This is space.       ";
    printf("\t8. rm_space(char* s): \"%s\"", s7);
    rm_space(s7);
    printf(" --> \"%s\"\n", s7);

    //9. int find
    printf("\t9. int find(char* h, char* n): \"%s\" contains \"%s\" at index %i\n", s1, s2, find(s1, s2));

    //10. char* ptr_to
    printf("\t10. char* ptr_to(char* h, char* n): The pointer for \"%s\" within \"%s\" is %p\n", s2, s1, ptr_to(s1, s2));

    //11. int is_empty
    printf("\t11. int is_empty(char* s): %u\n", is_empty(s1));

    //12. char* str_zip
    char* zipped = str_zip(s1, s2);
    printf("\t12. char* str_zip(char* s1, char* s2): \"%s\" + \"%s\" = \"%s\"\n", s1, s2, zipped);

    //13. void capitalize
    char s9[] = "thE quICk BrOWN fOX.";
    printf("\t13. void capitalize(char* s): \"%s\"", s9);
    capitalize(s9);
    printf(" --> \"%s\"\n", s9);

    //14. int strcmp_ign_case
    printf("\t14. int strcmp_ign_case(char* s1, char* s2): %i\n", strcmp_ign_case(s1, s2));

    //15. void take_last
    char s10[] = "Testing Stringies";
    int last = 6;
    printf("\t15. void take_last(char* s, int n): Last %i of \"%s\" is ", last, s10);
    take_last(s10, last);
    printf("\"%s\"\n", s10);

    //16. char* dedup
    char s11[] = "There's always money in the banana stand.";
    char* result = dedup(s11);
    printf("\t16. char* dedup(char* s): \"%s\"\n", result);

    //17. char* pad
    char s12[] = "Test String";
    printf("\t17. char* pad(char* s, int d): \"%s\" --> \"%s\"\n", s12, pad(s12, 8));

    //18. int ends_with_ignore_case
    printf("\t18. int ends_with_ignore_case(char* s, char* suff): %i\n", ends_with_ignore_case(s1, s2));

    //19. char* repeat
    char s19[] = "o";
    printf("\t19. char* repeat(char* s, int x, char sep): \"%s\"\n", repeat(s19, 8, '>'));

    //20. char* replace
    char s20[] = "Fiore X";
    char s21[] = "X";
    char s22[] = "sucks";
    printf("\t20. char* replace(char* s, char* pat, char* rep): \"%s\" --> \"%s\" in \"%s\" = \"%s\"\n", s21, s22, s20, replace(s20, s21, s22));

    //21. char* str_connect
    
    char** strs[] = { "Washington", "", "Adams", "Jefferson" };
    char** ptr = strs;
    printf("\t21. char* str_connect(char** s, int n, char c): \"%s\"\n", str_connect(strs, 4, '+'));

    //22. void rm_empties
    char** strs2[] = { "Washington", "", "", "", "", "Adams", "", "", "Jefferson", NULL };
    rm_empties(strs2);
    printf("\t22. void rm_empties(char** s): \"%s\"\n", str_connect(strs2, 2, '+'));

    //23. char** str_chop_all
    char s23[] = "The grass is greener on the other side";
    char** chopped = str_chop_all(s23, ' ');
    char** ptr2 = chopped;
    printf("\t23. char** str_chop_all(char* s, char c): ");
    while (*ptr2 != NULL) {
        printf("[\"%s\"] ", * ptr2);
        ptr2++;
    }
    
    printf("\nChecks complete.\n");
    return 0;
}