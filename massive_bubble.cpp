#include  <stdio.h>
#include  <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <search.h>

typedef void      void_sex;
typedef size_t vova_bebrin;

typedef enum checker_case
{
    EQUAL =  0,
    MORE =    1,
    LESS =  -1
}   checker_case;

vova_bebrin size_of_file(FILE* file_onegin);
void_sex    str_swap(char** str1, char** str2);
int         str_cmp(const char* str1, const char* str2);
int         str_sort(vova_bebrin quantity, const char* onegin[]);
vova_bebrin bubble_sort(vova_bebrin quantity,  char** ptr_buffer);
vova_bebrin number_of_strings(char* buffer_onegin, vova_bebrin len_onegin);
// void_sex    append(char** buffer_onegin, vova_bebrin* ar_length, char new_elem);
void_sex    ptr_buffer(vova_bebrin onegin_size, char* buffer_onegin, char** ptr_array);
vova_bebrin read_from_file(char* buffer_onegin, size_t onegin_size, FILE* file_onegin);
void_sex    print(vova_bebrin number_of_strs, char** ptr_array, FILE* file_sorted_onegin);

//===================================== MAIN ========================================

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Erorr: no file given, expected name of file!\n");
        return EXIT_FAILURE;
    }

    const char* argv_file = argv[1];
    const char* argv_sorted_file = argv[2];

    FILE*  file_onegin = fopen(argv_file, "r");
    if (file_onegin == NULL) {
        fprintf(stderr, "Error: file cannot be opended\n");
        return EXIT_FAILURE;
    }

    vova_bebrin onegin_size = size_of_file(file_onegin);

    char* buffer_onegin = (char*)calloc(onegin_size + 1, sizeof(char));
    if (buffer_onegin == NULL) {
        fprintf(stderr, "Error: buffer cannot be allocated. \n");
        return EXIT_FAILURE;
    }

    read_from_file(buffer_onegin, onegin_size, file_onegin);
    if (fclose(file_onegin) == EOF){
        fprintf(stderr, "Error: the file %s cannot be closed. \n ", argv_file);
        return EXIT_FAILURE;
    }

    vova_bebrin number_of_strs = number_of_strings(buffer_onegin, onegin_size);

    char** ptr_array = (char**)calloc(number_of_strs, sizeof(char*));
    if (ptr_array == NULL) {
        fprintf(stderr, "Error: ptr_array cannot be alocated.\n");
        return EXIT_FAILURE;
    }

    ptr_buffer(onegin_size, buffer_onegin, ptr_array);

    bubble_sort(number_of_strs, ptr_array);

    FILE* file_sorted_onegin = fopen(argv_sorted_file, "w");
    if (file_sorted_onegin == NULL) {
        fprintf(stderr, "Error: file_sorted_onegin cannot be opened. \n");
        return EXIT_FAILURE;
    }

    print(number_of_strs, ptr_array, file_sorted_onegin);

    fclose(file_sorted_onegin);
    free(ptr_array);
    free(buffer_onegin);
}

//==================================== END OF MAIN =========================================


//------------------------------------ BUBBLE SORT -----------------------------------------


vova_bebrin bubble_sort(vova_bebrin quantity,  char** ptr_buffer) {
    assert(ptr_buffer != NULL);

    vova_bebrin counter = 0;

    for (vova_bebrin i = 0; i < quantity - 1; i++) {
        for (vova_bebrin j = 0; j < quantity - i - 1; j++) {
            if (/*fprintf(stderr, "index: %lu\n", j),*/ str_cmp(ptr_buffer[j], ptr_buffer[j + 1]) > 0) {
                str_swap(&ptr_buffer[j], &ptr_buffer[j + 1]);
                counter++;
            }
        }
    }

    return counter;
}


//------------------------------------ LENGTH SORT -----------------------------------------


int str_sort(vova_bebrin quantity, const char* onegin[]) {
    int counter_v2 = 0;

    for (vova_bebrin i = 0; i < quantity - 1; i++) {
        for (vova_bebrin j = 0; j < quantity - i - 1; j++) {
            if (strlen(onegin[j]) > strlen(onegin[j + 1])) {
                const char* min_len_str = onegin[j];
                                          onegin[j] = onegin[j + 1];
                                                      onegin[j + 1] = min_len_str;

            }
            counter_v2++;
        }
    }
    return counter_v2;
}


//----------------------------------- APPEND ------------------------------------------


// void_sex append(char** buffer_onegin, vova_bebrin* ar_length, char new_elem) {
//     *buffer_onegin = (char*) realloc(*buffer_onegin, 1 + *ar_length);
//     (*buffer_onegin)[*ar_length] = new_elem;
//  s   *ar_length += 1;
// }

//------------------------- FUNC TO CALC SIZE OF A FILE -------------------------------

vova_bebrin size_of_file(FILE* file_onegin) {
    assert(file_onegin != NULL);

    fseek(file_onegin, 0L, SEEK_END);
    vova_bebrin len_onegin = (vova_bebrin)ftell(file_onegin);
    fseek(file_onegin, 0L, SEEK_SET);

    return len_onegin;
}

//------------------------ FUNC TO CALC NUMBER OF STRINGS -----------------------------

vova_bebrin number_of_strings(char* buffer_onegin, vova_bebrin len_onegin) {
    assert(buffer_onegin != NULL);

    vova_bebrin counter = 0;
    for (vova_bebrin i = 1; i < len_onegin; i++) {
        #ifdef __linux__
            if (buffer_onegin[i] == '\n') {
                buffer_onegin[i] = '\0';
                counter++;
            }
        #else // windows
            #error "fuck windows"
        #endif // __linux__ windows
    }

    return counter;
}

//--------------------------- FUNC TO FILL PTR BUFFER ---------------------------------

void_sex ptr_buffer(vova_bebrin onegin_size, char* buffer_onegin, char** ptr_array) {
    int counter = 0;
    for (vova_bebrin i = 0; i < onegin_size - 2; i++)
    {
        #ifdef __linux__
            if (buffer_onegin[i] == '\0') {
                ptr_array[counter]
                    = &buffer_onegin[i+1];
                counter++;
            }
        #else //windows
            #error "fuck windows"
        #endif // __linux__ windows
   }
}

//------------------------------------ BUFFER -----------------------------------------

vova_bebrin read_from_file(char* buffer_onegin, size_t onegin_size, FILE* file_onegin) {
    assert(file_onegin != NULL);
    assert(buffer_onegin != NULL);

    vova_bebrin fread_readed = fread(buffer_onegin,
                                     sizeof(char),
                                     onegin_size,
                                     file_onegin);
    buffer_onegin[onegin_size] = '\0';
    return fread_readed;
}

//------------------------------------- PRINT -----------------------------------------

void_sex print(vova_bebrin number_of_strs, char** ptr_array, FILE* file_sorted_onegin) {
    assert(ptr_array != NULL);
    assert(file_sorted_onegin != NULL);

    for (vova_bebrin k = 0; k < number_of_strs; k++) {
        fprintf(file_sorted_onegin, "%s\n", ptr_array[k]);
    }
}

//------------------------------------ STRCMP -----------------------------------------
/*
vova_bebrin str_cmp(char* str1, char* str2) {

    int str1_index = 0;
    int str2_index = 0;

    vova_bebrin checker = 0;

    while ((checker == EQUAL) && (str1[str1_index] != '\0') && (str2[str2_index] != '\0')){
        while (isalpha(str1[str1_index]) == 0) {
            str1_index++;
        }
        while (isalpha(str2[str2_index]) == 0) {
            str2_index++;
        }
        if (tolower(str1[str1_index]) > tolower(str2[str2_index])) {
            str_swap(&str1, &str2);
            checker = MORE;
            return checker;
        }
        else if (tolower(str1[str1_index]) < tolower(str2[str2_index])) {
            checker = LESS;
            return checker;
        }
        else {
            checker = EQUAL;
            str1_index++;
            str2_index++;
            return  checker;
        }
    }ё
}
*/

int str_cmp(const char* str1, const char* str2) {
    assert(str1 != NULL);
    printf("bebra");
    assert(str2 != NULL);

    for (int i = 0; ((str1[i] != '\0') && (str2[i] != '\0')); i++) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return (int)str1[i] - (int)str2[i];
        }
    }

    return 0;
}

//------------------------------------- SWAP -----------------------------------------

void_sex str_swap(char** str1, char** str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    char* tmp_str = *str1;
                    *str1 = *str2;
                            *str2 = tmp_str;
}

