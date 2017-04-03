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
        fprintf(stderr, "%s: to few arguments\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] != '-' || strlen(argv[1]) < 2) {
        fprintf(stderr, "%s: neighbourhoodType must start with '-' and exceed the length of one char\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[3][0] != '-' || strlen(argv[3]) < 2) {
        fprintf(stderr, "%s: inputMethod must start with '-' and exceed the length of one char\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[5][0] != '-' || strlen(argv[5]) < 2) {
        fprintf(stderr, "%s: outputMethod must start with '-' and exceed the length of one char\n", argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int OutputInfoParser(outputInfo *info, char **argv) {
    info->outputMethod = argv[5][1];
    if ((info->numberOfGenerations = StrToInt(argv[2])) == 0) {
        fprintf(stderr, "%s: numberOfGenerations must be an integer from the range of <1, %d>\n", argv[0], INT_MAX);
        return EXIT_FAILURE;
    }
    info->path = argv[6];

    return EXIT_SUCCESS;
}
