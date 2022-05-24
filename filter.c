/*
 * Implementation of functions that filter values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h> OTHER THAN
 * strcpy() and strlen()
 *****
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "filter.h"

#define NUL ('\0')

/*
 * YOU MAY FIND THIS FUNCTION USEFUL.
 * Return true if and only if character <c> is in string <s>.
 */
static bool includes(char c, char *s)
{
	while (*s && c != *s)
	{
		s++;
	}
	return c == *s;
}

/*
 * YOU MAY ALSO FIND THIS FUNCTION USEFUL.
 * Return true if and only if string <pre> is a prefix of string <s>.
 */
static bool prefix(char *s, char *pre)
{
	while (*pre && *s == *pre)
	{
		s++;
		pre++;
	}
	return *pre == NUL;
}

/*
 * Copy <string> to <result> while removing all occurrences of <ch>.
 */
void filter_ch_index(char string[], char result[], char ch)
{
	//used for indicies of string
	int i = 0;
	//indicies for indicies of result
	int j = 0;

	while (string[i] != '\0')
	{
		//if ch == string[i] skip the ch otherwise store string[i] into result
		if (ch == string[i])
		{
			++i;
		}
		else
		{
			result[j++] = string[i++];
		}
	}
	result[j] = '\0';
}

/*
 * Return a pointer to a string that is a copy of <string> with
 * all occurrences of <ch> removed. The returned string must occupy
 * the least possible dynamically allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_ch_ptr(char *string, char ch)
{
	int counter = 0;
	//used to count number of chars going into p_copy from p from string
	//then used as the # of bytes in the new malloc towards the end of the
	//function

	char *p_copy = malloc(strlen(string) + 1);
	//allocate space from heap

	char *p = p_copy;
	//point to fist byte at the address stored in p_copy

	while (*string)
	//iterate through the string until we reach its termination char
	{
		//while loop body: Checks to see if the current char in string is equal to that ch
		//if so proceed to the next char in string else store the char into p_copy using p
		// and move on to the next byte in p_copy as well as the next char in string
		if (*string == ch)
		{
			++string;
		}
		else
		{
			++counter;
			*p++ = *string++;
		}
	}
	*p = NUL;	
	p = malloc(counter + 1);
	strcpy(p, p_copy);
	free(p_copy);
	//freed allocated space for p_copy because we copied its content into new malloc
	//that requires less space
	return p;
}

/*
 * Copy <string> to <result> while removing all occurrences of
 * any characters in <remove>.
 */
void filter_any_index(char string[], char result[], char remove[])
{
	
	int h = 0; // for adjusted string
	int i = 0; //remove
	int j = 0; //orig string
	int k = 0; //result
	char copy[strlen(string)];
	for (int l = 0; l < strlen(string); l++)
	{
		copy[l] = string[l];
	}
	//use this copy of string instead of string because we do not want to change strings content
	//because it would result in the wrong string parameter for the following function calls

	if (strlen(remove) > 0)
	//if remove is empty then just pass in all of the current values in string into result
	//otherwise proceed to remove the char in remove from string and store in result
	{
		while (remove[i])
		//We check every char in copy for every one char in rem and check if they're equal or not
		//if equal move to next char in copy else store the current char in result and update
		//our copy array so were checking the new version that has elimanted the char from remove
		{
			while (copy[j])
			{
				if (remove[i] == copy[j])
				{
					++j;
				}
				else
				{
					result[h] = copy[j];
					copy[k] = result[h];
					++h;
					++k;
					++j;
				}
			}
			result[h] = '\0';
			copy[k] = '\0';
			h = 0;
			k = 0;
			j = 0;
			++i;
		}
	}
	else
	{
		for (int i = 0; i < strlen(string); i++)
		{
			result[k++] = string[i];
		}
	}
}

/*
 * Return a pointer to a copy of <string> after removing all
 * occurrrences of any characters in <remove>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_any_ptr(char *string, char *remove)
{
	//Only want to remove char from string if remove is not empy
	if (strlen(remove) > 0)
	{
		//create malloc that has the same value as the string passed in
		//We do this because in our while loop we are changing its content and updating  
		//constantly and we do not want to change the content of the original string
		char *iterator_copy_string = malloc(strlen(string) + 1);
		char *work_iterator_copy_string = strcpy(iterator_copy_string, string);

		//This malloc will contain the new string updated string every time we remove 
		//a char
		char *updated_string_copy = malloc(strlen(string) + 1);
		char *work_updated_string_copy = updated_string_copy;

		int length_final_copy_string = 0;
		//Nested loops - will check every char in work_iterator_copy_string for every char in remove
		//if char in remove is equal to char in work_iterator_copy_string then we want to skip over it 
		//because we do not want to add it to the work_updated_string_copy
		//if char in remove is not equal to char in work_iterator_copy_string then we add it to the 
		//work_updated_string_copy and continue looping
		while (*remove)
		{
			while (*work_iterator_copy_string)
			{
				if (*remove == *work_iterator_copy_string)
				{
					++work_iterator_copy_string;
				}
				else
				{
					//Will be the size of the final string
					++length_final_copy_string;
					*work_updated_string_copy++ = *work_iterator_copy_string++;
				}
			}
			//Here we add the terminating char to work_updated_string_copy and our result is 
			//a string that removed every instance the char in remove was in work_iterator_copy_string
			//Then we copy this into iterator_copy_string because we want to loop over the updated 
			//string in order to get rid of any other char from remove left in the updated string
			*work_updated_string_copy = '\0';
			strcpy(iterator_copy_string, updated_string_copy);
			//Here we set the assign the malloc pointers to our work pointers so when were looping 
			//we are starting at the 1st byte everytime.
			work_iterator_copy_string = iterator_copy_string;
			work_updated_string_copy = updated_string_copy;
			++remove;
		}
		//This malloc will store our final string that we want and at its new more efficient size
		char *final_copy_string = malloc(length_final_copy_string + 1);
		strcpy(final_copy_string, updated_string_copy);
		//We free both mallocs from above 
		free(iterator_copy_string);
		free(updated_string_copy);
		return final_copy_string;
	}
	else
	{
		//Return the original string if nothing is in remove
		char *final_copy_string = malloc(strlen(string) + 1);
		strcpy(final_copy_string, string);
		return final_copy_string;
	}
}
/* 
 * occurrrences of the substring <substr>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE ARRAY INDEXING.
 *****
 */
char *filter_substr(char *string, char *substr)
{
	return strcpy(malloc(1), ""); // placeholder
}

