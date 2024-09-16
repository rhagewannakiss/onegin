#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef void void_sex;
typedef size_t vova_bebrin;

vova_bebrin bubble_sort(vova_bebrin quantity,  char** ptr_buffer);
int str_sort(vova_bebrin quantity, const char* onegin[]);
void_sex append(char** buffer_onegin, vova_bebrin* ar_length, char new_elem);
vova_bebrin size_of_file(FILE* file_onegin);
vova_bebrin quantity(char* buffer_onegin, vova_bebrin len_onegin);
void_sex ptr_buffer(vova_bebrin onegin_size, char* buffer_onegin, char** ptr_array);

//===================================== MAIN ========================================

int main()
{
    FILE* file_onegin = fopen("Evgeniy.txt", "r");
    assert(file_onegin != NULL);

    vova_bebrin onegin_size = size_of_file(file_onegin);
    // printf("onegin size: %lu\n", onegin_size);

    char* buffer_onegin = (char*)calloc(onegin_size + 1, sizeof(char));
    assert(buffer_onegin != NULL);

    assert(file_onegin != NULL);
    fread(buffer_onegin,
          sizeof(char),
          onegin_size,
          file_onegin);
    // perror("read failure");
    // printf("readed: %lu\n", readed);

    buffer_onegin[onegin_size] = '\0';

    vova_bebrin number_of_strs = quantity(buffer_onegin, onegin_size);

    char** ptr_array = (char**)calloc(number_of_strs, sizeof(char*));
    assert(ptr_array != NULL);

    // разными схемами расставить указатели в буффер

    ptr_buffer(onegin_size, buffer_onegin, ptr_array);
    // for (size_t i = 0; i < number_of_strs; i++) {
    //     fprintf(stderr, "ptr[%lu]: %p\n", i, ptr_array[i]);
    // }

    vova_bebrin swaped_in_sort = bubble_sort(number_of_strs, ptr_array);
    // fprintf(stderr, "swapped in sort: %lu\n", swaped_in_sort);

    // for (vova_bebrin k = 0; k < onegin_size; k++)
    // {
    //     printf("%c", buffer_onegin[k]);
    //     if (buffer_onegin[k] == '\0') {
    //         putchar('\n');
    //     }
    // }

    for (vova_bebrin k = 0; k < number_of_strs; k++)
    {
        printf("%s\n", ptr_array[k]);
    }

    free(buffer_onegin);
    free(ptr_array);
    fclose(file_onegin);
}

//==================================== END OF MAIN =========================================


//------------------------------------ BUBBLE SORT -----------------------------------------



vova_bebrin bubble_sort(vova_bebrin quantity,  char** ptr_buffer)
{
    assert(ptr_buffer != NULL);

    vova_bebrin counter = 0;

    for (vova_bebrin i = 0; i < quantity - 1; i++)
    {
        for (vova_bebrin j = 0; j < quantity - i - 1; j++)
        {
            // fprintf(stderr, "j: %lu ptr_buffer[j]: %p ptr_buffer[j + 1]: %p\n", j, ptr_buffer[j], ptr_buffer[j + 1]);
            //if (strlen(ptr_buffer[j]) > strlen(ptr_buffer[j + 1]))
            if (strcmp(ptr_buffer[j], ptr_buffer[j+1]) > 0)
            {
                char* min_ptr = ptr_buffer[j];
                                ptr_buffer[j] = ptr_buffer[j + 1];
                                                ptr_buffer[j + 1] = min_ptr;
                counter++;
            }
        }
    }

    return counter;
}


//------------------------------------ LENGTH SORT -----------------------------------------


int str_sort(vova_bebrin quantity, const char* onegin[])
{
    int counter_v2 = 0;

    for (vova_bebrin i = 0; i < quantity - 1; i++)
    {
        for (vova_bebrin j = 0; j < quantity - i - 1; j++)
        {
            if (strlen(onegin[j]) > strlen(onegin[j + 1]))
            {
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


void_sex append(char** buffer_onegin, vova_bebrin* ar_length, char new_elem)
{
    *buffer_onegin = (char*) realloc(*buffer_onegin, 1 + *ar_length);
    (*buffer_onegin)[*ar_length] = new_elem;
    *ar_length += 1;
    //return
}

//------------------------- FUNC TO CALC SIZE OF A FILE -------------------------------

vova_bebrin size_of_file(FILE* file_onegin)
{
    assert(file_onegin != NULL);

    fseek(file_onegin, 0L, SEEK_END);
    vova_bebrin len_onegin = (vova_bebrin)ftell(file_onegin);
    fseek(file_onegin, 0L, SEEK_SET);

    return len_onegin;
}

//------------------------ FUNC TO CALC NUMBER OF STRINGS -----------------------------

vova_bebrin quantity(char* buffer_onegin, vova_bebrin len_onegin)
{
    assert(buffer_onegin != NULL);

    vova_bebrin counter = 0;
    for (vova_bebrin i = 1; i < len_onegin; i++) {
        if (buffer_onegin[i] == '\n') {
            buffer_onegin[i] = '\0';
            if (buffer_onegin[i - 1] == '\r') {
                buffer_onegin[i - 1] = '\0';
            }
            counter++;
        }
    }

    return counter;
}

void_sex ptr_buffer(vova_bebrin onegin_size, char* buffer_onegin, char** ptr_array) {
    int counter = 0;
    for (vova_bebrin i = 0; i < onegin_size - 2; i++)
    {
        if (buffer_onegin[i] == '\0'){
            // fprintf(stderr, "ptr found, counter: %d\n", counter);
            if (buffer_onegin[i+1] == '\0'){
                ptr_array[counter] = &buffer_onegin[i+2];
            }
            else{
                ptr_array[counter] = &buffer_onegin[i+1];
            }
            counter++;
        }
    }
}