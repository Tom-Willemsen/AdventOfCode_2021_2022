#include "file_loading.h"

FILE* open_arg_as_file_or_exit(int argc, char** argv) {
    if (argc == 0) {
        fprintf(stderr, "Usage: program <input filepath>\n");
        exit(EXIT_FAILURE);
    } else if (argc == 1) {
        fprintf(stderr, "Usage: %s <input filepath>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    FILE* fptr = fopen(argv[1], "r");
    
    if (fptr == NULL) {
        fprintf(stderr, "File at '%s' could not be opened\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    return fptr;
}

char** load_file_as_str_arr(FILE* fptr, uint64_t *size) {
    uint64_t l = 0;
    size_t linelength;
    char **data = NULL;
    char* buffer = NULL;
    
    while (getline(&buffer, &linelength, fptr) != -1){
        if (data == NULL) {
            data = calloc((l+1), sizeof(char*));
        } else {
            data = realloc(data, (l+1) * sizeof(char*));
        }
        data[l] = calloc(linelength + 1, sizeof(char));
        strcpy(data[l], buffer);
        
        free(buffer);
        buffer = NULL;
        l++;
    }

    free(buffer);
    
    *size = l;
    return data;
}

uint8_t** load_dense_file_as_uint8_arr(FILE* fptr, uint64_t *y_size, uint64_t *x_size) {
    uint64_t x, y, lines = 0, linelength = 0, maxlinelength = 0;
    int c;
    uint8_t **data = NULL;
    
    while ((c = fgetc(fptr)) != EOF) {
        if (c == '\n') {
            lines++;
            if (linelength > maxlinelength) {
                maxlinelength = linelength;
            }
            linelength = 0;
            continue;
        }
        linelength++;
    }
    
    if (lines == 0) {
        puts("file format error, no lines");
        exit(EXIT_FAILURE);
    }
    
    data = calloc(lines, sizeof(uint8_t*));
    for (y=0; y<lines; ++y) {
        data[y] = calloc(maxlinelength, sizeof(uint8_t));
    }
    
    rewind(fptr);
    
    x = 0;
    y = 0;
    while ((c = fgetc(fptr)) != EOF) {
        if (c == '\n') {
            y++;
            x=0;
            continue;
        }
        if (c < '0' || c > '9' || y > lines || x > maxlinelength) {
            printf("file format error, c=%d, x=%"PRIu64", y=%"PRIu64", lines=%"PRIu64", maxlinelength=%"PRIu64"\n", c, x, y, lines, maxlinelength);
            exit(EXIT_FAILURE);
        }
        data[y][x] = c - '0';
        x++;
    }
    
    *y_size = lines;
    *x_size = maxlinelength;
    return data;
}

void free_str_arr(char** const str_arr, const uint64_t size) {
    for (uint64_t i=0; i<size; ++i) {
        free(str_arr[i]);
    }
    if (size > 0) {
        free(str_arr);
    } else {
        assert(str_arr == NULL);
    }
}

list_i64* load_file_as_list_i64(FILE* fptr) {
    list_i64* data = list_i64_init(1);
    int64_t value;
    while(fscanf(fptr, "%" SCNd64, &value) != EOF) {
        list_i64_push_back(data, value);
    }
    return data;
}
