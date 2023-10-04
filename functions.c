#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "string_library.h"

//Assignment 08 Custom helper functions
int strlen(char* s) {
	char* ptr = s;
	while (*ptr != '\0') {
		++ptr;
	}
	return ptr - s;
}
int strslen(char** s, int n) {
	char** ptr = s;
	int length = 0;
	for (int i = 0; i < n; i++) {
		length = length + strlen(*ptr);
		ptr++;
	}
	return length;
}

int find_char(char* h, char n) {
	char* ptr = h;
	int index = -1;

	while (*ptr != '\0') {
		if (*ptr == n) {
			index = ptr - h;
			return index;
		}
		ptr++;
	}
	return -1; //occurence of n is not found
}


//CIS2107 Assignment 08 functions
int all_letters(char* s) {
	int i = 0, numUpper = 0, numLetters = 0;
	char* ptr = s;

	if (s == NULL) return 0;
	
	//iterate through each character
	while (*ptr != '\0') {
		//if uppercase, upper-case counter increments
		if (isupper(*ptr)) numUpper++;
		if ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z')) numLetters++;
		ptr++;
	}
	if (numLetters == 0) return 0; //if string is empty or only contains non-alphabet characters
	if (numUpper == 0 || numUpper == numLetters)
		return 1;
	else
		return 0;
}

int num_in_range(char* s1, char b, char t) {
	int numBetween = 0;
	char* ptr = s1;

	if (s1 == NULL || b == NULL || t == NULL) return 0;

	while (*ptr != '\0') {
		if (*ptr >= b && *ptr <= t) numBetween++;
		ptr++;
	}
	return numBetween;
}

int diff(char* s1, char* s2) {
	char* ptr1 = s1, * ptr2 = s2;
	int numSubst = 0, numInsert = 0, numDelete = 0;

	if (s1 == NULL || s2 == NULL) return 0;

	//Case 1: s1 and s2 are the same length --> only letter substitutions need to be made
	//Case 2: s1 is longer than s2 --> letter subst. and deletions need to be made
	//Case 3: s1 is shorter than s2 --> letter subst. and insertions need to be made
	//Return # of subst., instertions, and deletions necessary
	while (*ptr1 != '\0' && *ptr2 != '\0') {
		if (*ptr1 != *ptr2) numSubst++;
		ptr1++;
		ptr2++;
	}
	if (*ptr1 != '\0' && *ptr2 == '\0') { //s1 is longer than s2, deletions needed
		while (*ptr1 != '\0') ++ptr1; // finish ptr1 iterations
		numDelete = (ptr1 - s1) - (ptr2 - s2);
	}
	if (*ptr1 == '\0' && *ptr2 != '\0') { //1 is shorter than s2, insertions needed
		while (*ptr2 != '\0') ++ptr2;
		numInsert = (ptr2 - s2) - (ptr1 - s1);
	}
	return numSubst + numDelete + numInsert;
}

void shorten(char* s, int new_len) {
	if (strlen(s) <= new_len) return;
	s[new_len] = '\0';
}

int len_diff(char* s1, char* s2) {
	return strlen(s1) - strlen(s2);
}

void rm_left_space(char* s) {
	char* ptr = s;
	int space = 0;
	while (*ptr == ' ') {
		space++;
		ptr++;
	}
	int newSize = strlen(s) - space;
	for (int i = 0; i < newSize; i++) {
		s[i] = *ptr;
		ptr++;
	}
	s[newSize] = '\0';
}

void rm_right_space(char* s) {
	char* ptr = s;
	int space = 0;
	while (*ptr != '\0') {
		if (*ptr == ' ') {
			space++;
		}
		else {
			space = 0;
		}
		ptr++;
	}
	s[(ptr - s) - space] = '\0';
}

void rm_space(char* s) {
	rm_right_space(s);
	rm_left_space(s);
}

int find(char* h, char* n) {
	char* ptr1 = h, * ptr2 = n;
	int index = 0;

	if (strlen(n) > strlen(h)) return -1;

	if (*ptr1 == '\0' && *ptr2 == '\0') return -1; //both strings are empty, therefore n is contained in h at index 0
	while (*ptr1 != '\0') {
		if (*ptr1 == *ptr2) {
			index = ptr1 - h;
			while (*ptr1 == *ptr2 && *ptr2 != '\0') {
				ptr1++;
				ptr2++;
			}
			if (*ptr2 == '\0') return index; //occurence of n is found at index (ptr1 - h)
			ptr2 = n; //reset pointer 2
		}
		ptr1++;
	}
	return -1; //occurence of n is not found
}

char* ptr_to(char* h, char* n) {
	int index = find(h, n);
	if (index == -1) return NULL;
	char* ptr = h[index];
	return ptr;
} // NEED TO TEST WRITING A STRING WITH A POINTER

int is_empty(char* s) {
	char* ptr = s;
	if (s == NULL) return 1;
	if (s == "") return 1;
	while (*ptr != '\0') {
		if (!isspace(*ptr)) return 0;
		ptr++;
	}
	return 1;
} 

char* str_zip(char* s1, char* s2) {
	char* ptr1 = s1, * ptr2 = s2;
	char* newString = (char*)malloc((strlen(s1) + strlen(s2)) * sizeof(char));
	char* newStringPtr = newString;

	*newStringPtr = '\0';

	while (*ptr1 != '\0' && *ptr2 != '\0') {
		*newStringPtr = *ptr1;
		newStringPtr++;
		*newStringPtr = *ptr2;
		newStringPtr++;
		ptr1++;
		ptr2++;
	}
	if (*ptr1 == '\0') {
		while (*ptr2 != '\0') {
			*newStringPtr = *ptr2;
			ptr2++;
			newStringPtr++;
		}
		*newStringPtr = '\0';
		return newString;
	}
	while (*ptr1 != '\0') {
		*newStringPtr = *ptr1;
		ptr1++;
		newStringPtr++;
	}
	*newStringPtr = '\0';
	return newString;
} // Need to handle if string memory is exceeded

void capitalize(char* s) {
	char* ptr = s;

	while (*ptr != '\0') {
		if ((*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z')) {
			s[ptr - s] = toupper(*ptr);
			ptr++;
			while (*ptr != '\0' && *ptr != ' ') {
				s[ptr - s] = tolower(*ptr);
				ptr++;
			}
		}
		ptr++;
	}
}

int strcmp_ign_case(char* s1, char* s2) {
	char* ptr1 = s1, * ptr2 = s2;
	*ptr1 = tolower(*ptr1);
	*ptr2 = tolower(*ptr2);

	//Base cases
	if (*ptr1 == '\0' && *ptr2 == '\0') return 0;
	if (*ptr1 == '\0') return -1;
	if (*ptr2 == '\0') return 1;
	if (*ptr1 > *ptr2) return 1;
	if (*ptr1 < *ptr2) return -1;
	ptr1++;
	ptr2++;
	//Recurse
	strcmp_ign_case(ptr1, ptr2);
}

void take_last(char* s, int n) {
	if (strlen(s) <= n) return;
	char* ptr = s;
	for (int i = 0; i < (strlen(s) - n); i++) ptr++;
	for (int i = 0; i < n; i++) {
		s[i] = *ptr;
		ptr++;
	}
	s[n] = '\0';
}

char* dedup(char* s) {
	if (s == NULL) return NULL;
	char* newString = (char*)malloc(strlen(s) * sizeof(char));
	char* newStringPtr = newString;
	char* ptr = s;

	*newStringPtr = '\0';
	while (*ptr != '\0') {
		if (find_char(newString, *ptr) == -1) {
			*newStringPtr = *ptr;
			newStringPtr++;
		}
		ptr++;
		*newStringPtr = '\0';
	}
	return newString;
} //Not done

char* pad(char* s, int d) {
	if (strlen(s) % d == 0 && strlen(s) % 2 == 0) return s;
	char* newString = (char*)malloc((strlen(s) + d) * sizeof(char));
	char* newStringPtr = newString;
	char* ptr = s;
	while (*ptr != '\0') {
		*newStringPtr = *ptr;
		newStringPtr++;
		ptr++;
	}
	*newStringPtr = '\0';

	while (strlen(newString) % d != 0 || strlen(newString) % 2 != 0) {
		*newStringPtr = ' ';
		newStringPtr++;
		*newStringPtr = '\0';
	}
	return newString;
} // Not done

int ends_with_ignore_case(char* s, char* suff) {
	char* ptr1 = s, * ptr2 = suff;

	if (strlen(s) < strlen(suff)) return 0;
	for (int i = 0; i < strlen(s) - strlen(suff); i++) {
		ptr1++;
	}
	while (*ptr1 != '\0' && *ptr2 != '\0') {
		if (*ptr1 != *ptr2) return 0;
		ptr1++;
		ptr2++;
	}
	return 1;
}

char* repeat(char* s, int x, char sep) {
	if (s == NULL) return NULL;

	char* newString = (char*)malloc((strlen(s) + x - 1) * x * sizeof(char*));
	char* newStringPtr = newString;
	char* ptr = s;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < strlen(s); j++) {
			*newStringPtr = *ptr;
			newStringPtr++;
			ptr++;
		}
		if (*newStringPtr != '\0') {
			*newStringPtr = sep;
			newStringPtr++;
		}
		ptr = s;
	}
	newStringPtr--;
	*newStringPtr = '\0';
	return newString;
}

char* replace(char* s, char* pat, char* rep) {
	char* newString = (char*)malloc((strlen(s) + strlen(rep)) * sizeof(char*));
	char* newStringPtr = newString;
	char* ptr1 = s;
	char* ptr2 = rep;

	while (*ptr1 != '\0') {
		if (find(ptr1, pat) != -1) {
			int index = find(ptr1, pat);
			if (index == 0) {
				while (*ptr2 != '\0') {
					*newStringPtr = *ptr2;
					ptr2++;
					newStringPtr++;
				}
				for (int i = 0; i < strlen(pat); i++) { //move pointer past pat in string
					ptr1++;
				}
			}
			else {
				for (int i = 0; i < index; i++) { //reach next instance of pat
					*newStringPtr = *ptr1;
					ptr1++;
					newStringPtr++;
				}
				while (*ptr2 != '\0') {
					*newStringPtr = *ptr2;
					ptr2++;
					newStringPtr++;
				}
				for (int i = 0; i < strlen(pat); i++) { //move pointer past pat in string
					ptr1++;
				}
			}
		}
		else {
			while (*ptr1 != '\0') {
				*newStringPtr = *ptr1;
				ptr1++;
				newStringPtr++;
			}
		}
		ptr2 = rep;
	}
	*newStringPtr = '\0';
	return newString;
}

char* str_connect(char** strs, int n, char c) {
	char* newString = (char*)malloc(((strslen(strs, n)) + (c * n - 1)) * sizeof(char*));
	char* newStringPtr = newString;
	char** ptr = strs;
	char* subPtr = *ptr;
	for (int i = 0; i < n; i++) {
		while (*subPtr != '\0') {
			*newStringPtr = *subPtr;
			newStringPtr++;
			subPtr++;
		}
		ptr++;
		subPtr = *ptr;
		*newStringPtr = c;
		newStringPtr++;
	}
	newStringPtr--;
	*newStringPtr = '\0';
	return newString;
}

void rm_empties(char** words) {
	char** curr = words;
	char** next = words;
	next++;
	while (*next != NULL && *curr != NULL) {
		if (strlen(*curr) == 0) {
			while (*next != NULL) {
				*curr = *next;
				curr++;
				next++;
			}
			*curr = NULL;
			curr = words;
			next = words;
			next++;
		}
		curr++;
		next++;
	}

}

char** str_chop_all(char* s, char c) {
	char** newArray = (char**)malloc(strlen(s) * strlen(s) * sizeof(char**));
	char** strPtr = newArray;
	char* str = (char*)malloc(strlen(s) * sizeof(char*));
	char* ptr = s;
	char* lagPtr = str;
	char* ptr2 = str;
	int size = 0;

	while (*ptr != '\0') {
		while (*ptr != c && *ptr != '\0') {
			*ptr2 = *ptr;
			ptr2++;
			ptr++;
			size++;
		}
		if (*ptr != '\0') {
			*ptr2 = '\0';
			*strPtr = lagPtr;
			ptr2++;
			//strPtr = strPtr + (ptr2 - lagPtr);
			strPtr++;
			lagPtr = ptr2;
			//location in memory needs to go beyond ptr2
			size = 0;
			ptr++;
		}
	}
	*ptr2 = '\0';
	*strPtr = lagPtr;
	//strPtr = strPtr + (ptr2 - lagPtr);
	strPtr++;
	*strPtr = NULL;
	return newArray;
}

