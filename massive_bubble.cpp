#include  <stdio.h>
#include  <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <search.h>

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//сделать массив из функций strcmp straight + reverse
//чтобы функция бубле сорт (в дальнейшем в идеале кусорт) в качестве еще одного аргумента запрашивала указатель на элоемент массива функций т.е. укащатель на функцию
//сама подставляла его в момент где нужен стркмп и как итог дважды одним вызовом все делала
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

typedef int (*func_ptr)(int, int);


typedef void      void_sex;
typedef size_t vova_bebrin;

typedef enum checker_case {
    EQUAL =          0,
    MORE =           1,
    LESS =          -1,
    ERROR_NULL_PTR = 2
}   checker_case;

typedef struct poltorashka {
    char** start_ptr_array;
    char**   end_ptr_array;
}   poltorashka;

void_sex    ptr_buffer(vova_bebrin onegin_size, char* buffer_onegin, char** start_ptr_array, char** end_ptr_array);
void_sex    print(vova_bebrin number_of_strs, char** start_ptr_array, FILE* file_sorted_onegin);
vova_bebrin read_from_file(char* buffer_onegin, size_t onegin_size, FILE* file_onegin);
vova_bebrin number_of_strings(char* buffer_onegin, vova_bebrin len_onegin);
vova_bebrin straight_sort(vova_bebrin quantity,  char** ptr_buffer);
int         reverse_str_cmp(struct poltorashka ptr_struct, int i);
int         str_sort(vova_bebrin quantity, const char* onegin[]);
int         str_cmp(const char* str1, const char* str2);
void_sex    str_swap(char** str1, char** str2);
vova_bebrin size_of_file(FILE* file_onegin);

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

    char** start_ptr_array = (char**)calloc(number_of_strs + 1, sizeof(char*));
    if (start_ptr_array == NULL) {
        fprintf(stderr, "Error: start_ptr_array cannot be alocated.\n");
        return EXIT_FAILURE;
    }

    char**   end_ptr_array = (char**)calloc(number_of_strs + 1, sizeof(char*));
    if (start_ptr_array == NULL) {
        fprintf(stderr,    "Error: end_ptr_array cannot be alocated.\n");
        return EXIT_FAILURE;
    }

    struct poltorashka ptr_struct = { start_ptr_array,
                                      end_ptr_array    };
    assert(ptr_struct.start_ptr_array != NULL);
    assert(ptr_struct.end_ptr_array   != NULL);

    ptr_buffer(onegin_size, buffer_onegin, start_ptr_array, end_ptr_array);

    straight_sort(number_of_strs, start_ptr_array);

    FILE* file_sorted_onegin = fopen(argv_sorted_file, "w");
    if (file_sorted_onegin == NULL) {
        fprintf(stderr, "Error: file_sorted_onegin cannot be opened. \n");
        return EXIT_FAILURE;
    }

    print(number_of_strs, start_ptr_array, file_sorted_onegin);

    fclose(file_sorted_onegin);
    free(start_ptr_array);
    free(buffer_onegin);
}

//==================================== END OF MAIN =========================================


//------------------------------------ BUBBLE SORT -----------------------------------------

vova_bebrin straight_sort(vova_bebrin quantity,  char** ptr_buffer) {
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

//---------------------------- FUNC TO FILL PTR BUFFER --------------------------------

void_sex ptr_buffer(vova_bebrin onegin_size, char* buffer_onegin, char** start_ptr_array, char** end_ptr_array) {
    int counter = 0;
    for (vova_bebrin i = 0; i < onegin_size; i++)
    {
        #ifdef __linux__
            if (buffer_onegin[i] == '\0') {
                start_ptr_array[counter]
                    = &buffer_onegin[i + 1];
                end_ptr_array[counter]
                    = &buffer_onegin[i];
                counter++;
            }
        #else //windows
            #error "fuck windows"
        #endif // __linux__ windows
   }
}

//------------------------------------ BUFFER -----------------------------------------

vova_bebrin read_from_file(char* buffer_onegin, size_t onegin_size, FILE* file_onegin) {
    assert(file_onegin   != NULL);
    assert(buffer_onegin != NULL);

    vova_bebrin fread_readed = fread(buffer_onegin,
                                     sizeof(char),
                                     onegin_size,
                                     file_onegin);
    buffer_onegin[onegin_size] = '\0';
    return fread_readed;
}

//------------------------------------- PRINT -----------------------------------------

void_sex print(vova_bebrin number_of_strs, char** start_ptr_array, FILE* file_sorted_onegin) {
    assert(start_ptr_array    != NULL);
    assert(file_sorted_onegin != NULL);

    for (vova_bebrin k = 0; k < number_of_strs; k++) {
        fprintf(file_sorted_onegin, "%s\n", start_ptr_array[k]);
    }
}

//------------------------------------ STRCMP -----------------------------------------

int str_cmp(const char* str1, const char* str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    int str1_index = 0;
    int str2_index = 0;

    while ((str1[str1_index] != '\0') && (str2[str2_index] != '\0')) {
        if (tolower(str1[str1_index]) != tolower(str2[str2_index])) {
            return  (int)str1[str1_index] - (int)str2[str2_index];
        }
        str1_index++;
        str2_index++;
    }
    if (strlen(str1) != strlen(str2)) {
        return strlen(str1) - strlen(str2);
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

//--------------------------------- REVERSE STRCMP ------------------------------------

int reverse_str_cmp(struct poltorashka ptr_struct, int i) {

    assert(ptr_struct.end_ptr_array[i]       != NULL);
    assert(ptr_struct.end_ptr_array[i + 1]   != NULL);
    assert(ptr_struct.start_ptr_array[i]     != NULL);
    assert(ptr_struct.start_ptr_array[i + 1] != NULL);

    char* str1_ind_end =         ptr_struct.end_ptr_array[i];
    char* str2_ind_end =     ptr_struct.end_ptr_array[i + 1];
    char* str1_ind_start =     ptr_struct.start_ptr_array[i];
    char* str2_ind_start = ptr_struct.start_ptr_array[i + 1];

    long int len_str1 = str1_ind_end - str1_ind_start;
    long int len_str2 = str2_ind_end - str2_ind_start;

    while ((len_str1 != 0) && (len_str2 != 0)) {
        if (tolower(str1_ind_start[len_str1]) != tolower(str2_ind_start[len_str2])) {
            return  (int)str1_ind_start[len_str1] - (int)str2_ind_start[len_str2];
        }
        len_str1--;
        len_str2--;
    }
    if (strlen(str1_ind_start) != strlen(str2_ind_start)) {
        return strlen(str1_ind_start) - strlen(str2_ind_start);
    }

    return 0;
}
