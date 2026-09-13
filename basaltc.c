#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_FILENAME_LEN 512
bool error_exist = false;
typedef struct {
    char filename[MAX_FILENAME_LEN];
    bool valid_command;
    bool is_llvm;
    bool wants_help;
} compiler_arguments;
void print_help(const char *prog_name) {
//leave blank for later
    }
compiler_arguments parse_inputs(int argc, char *argv[]) {
    compiler_arguments args = {
        .valid_command = false,
        .is_llvm = false,
        .wants_help = false,
        .filename = ""
    };
    if (argc < 2) {
        return args;
    }
    args.valid_command = true;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "help") == 0) {
            args.wants_help = true;
        } else if (strcmp(argv[i], "--llvm") == 0) {
            args.is_llvm = true;
        } else {
            strncpy(args.filename, argv[i], sizeof(args.filename) - 1);
            args.filename[sizeof(args.filename) - 1] = '\0';
        }
    }
    return args;
}
int main(int argc, char *argv[]) {
    compiler_arguments config = parse_inputs(argc, argv);
    if (!config.valid_command || config.wants_help || strlen(config.filename) == 0) {
        print_help(argv[0]);
        return config.wants_help ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    FILE *file = fopen(config.filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: File not found '%s', Next time enter a Valid file.\n", config.filename);
        error_exist = true;
        return EXIT_FAILURE;
    }
    fclose(file);
    return EXIT_SUCCESS;
}
