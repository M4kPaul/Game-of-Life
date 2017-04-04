#include "iocontrol.h"

int Read(char inputMethod, char *fileName, grid_t *grid) {
    switch (inputMethod) {
        case 'p':
        case 'P':
            return ReadPngToGrid(fileName, grid);
        case 'b':
        case 'B':
            return ReadBMP(fileName, grid);
        default:
            fprintf(stderr, "iocontrol.c: input method -%c does not exist\n", inputMethod);
            return EXIT_FAILURE;
    }
}

int IntLength(int x) {
    int res;

    res = 1;
    while (x / 10) {
        x /= 10;
        res++;
    }

    return res;
}

char *FileNameBuilder(outputInfo *info) {
    int length;
    char *result;
    char extension[10];
    int numberOfZeroes;
    char *partialFilePath;

    length = (int)strlen(info->path);
    length += IntLength(info->numberOfGenerations);

    switch (info->outputMethod) {
        case 'p':
        case 'P':
            strncpy(extension, ".png", 5);
            length += 5;
            break;
        default:
            strncpy(extension, "", 1);
            length += 1;
            break;
    }

    partialFilePath = calloc(sizeof *partialFilePath * (length + 1), sizeof *partialFilePath);
    result = calloc(sizeof *partialFilePath, sizeof *result);

    strncat(partialFilePath, info->path, strlen(info->path));

    numberOfZeroes = IntLength(info->numberOfGenerations) - IntLength(info->generation);
    while (numberOfZeroes > 0) {
        strncat(partialFilePath, "0", 1);
        numberOfZeroes--;
    }

    snprintf(result, (size_t)length, "%s%d%s", partialFilePath, info->generation, extension);

    return result;
}

int Write(grid_t *grid, outputInfo *info) {
    char *fileName;

    fileName = FileNameBuilder(info);
    
    switch (info->outputMethod) {
        case 'p':
        case 'P':
            return WriteGridToPng(fileName, grid);
        default:
            fprintf(stderr, "iocontrol.c: input method -%c does not exist\n", info->outputMethod);
            return EXIT_FAILURE;
    }
}

int StrToInt(char *number) {
    long int tmp;

    tmp = strtol(number, NULL, 10);

    if (tmp <= 0 || tmp > INT_MAX) {
        return 0;
    }

    return (int)tmp;
}

int CheckArgs(int argc, char **argv) {
    if (argc < 7) {
        fprintf(stderr, "iocontrol.c: to few arguments\n");
        return EXIT_FAILURE;
    }

    if (argv[1][0] != '-' || strlen(argv[1]) < 2) {
        fprintf(stderr, "iocontrol.c: neighbourhoodType must start with '-' and exceed the length of one char\n");
        return EXIT_FAILURE;
    }

    if (argv[3][0] != '-' || strlen(argv[3]) < 2) {
        fprintf(stderr, "iocontrol.c: inputMethod must start with '-' and exceed the length of one char\n");
        return EXIT_FAILURE;
    }

    if (argv[5][0] != '-' || strlen(argv[5]) < 2) {
        fprintf(stderr, "iocontrol.c: outputMethod must start with '-' and exceed the length of one char\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int OutputInfoParser(outputInfo *info, int argc, char **argv) {
    info->outputMethod = argv[5][1];
    if ((info->numberOfGenerations = StrToInt(argv[2])) == 0) {
        fprintf(stderr, "iocontrol.c: numberOfGenerations must be an integer from the range of <1, %d>\n", INT_MAX);
        return EXIT_FAILURE;
    }
    info->path = argv[6];

    if (argc > 7) {
        if (strcmp(argv[7], "-t") != 0 && strcmp(argv[7], "-T") != 0) {
            fprintf(stderr, "iocontrol.c: the will of using multi threading must be indicated with the -t option\n");
            return EXIT_FAILURE;
        }

        if (argc < 9) {
            fprintf(stderr, "iocontrol.c: numberOfThreads must be specifed when using multi threading\n");
            return EXIT_FAILURE;
        }

        if ((info->numberOfThreads = StrToInt(argv[8])) == 0) {
            fprintf(stderr, "iocontrol.c: numberOfThreads must be a positive integer\n");
            return EXIT_FAILURE;
        }
    } else {
        info->numberOfThreads = 0;
    }

    return EXIT_SUCCESS;
}
