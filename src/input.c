#include "input.h"

static const int white_chars[] = {32, 9, 11, 12, 13};
static const int WHITE_COUNT = sizeof white_chars / sizeof(int);

static bool is_white_char(int x) {
    for (int i = 0; i < WHITE_COUNT; i++)
        if (x == white_chars[i])
            return true;

    return false;
}

static bool is_letter(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static bool is_digit(int c) {
    return c >= '0' && c <= '9';
}

static bool read_first_char(char *type, bool *return_value, bool *ignore,
                            bool *error) {
    int c;
    bool dont_read = false;

    c = getchar();

    if (c == '\n') {
        *ignore = true;
        dont_read = true;
    }

    if (c == EOF) {
        *ignore = true;
        dont_read = true;
        *return_value = false;
    }

    if (dont_read) {
        return dont_read;
    }

    if (c == '#')
        *ignore = true;

    if (is_letter(c)) {
        *type = (char)c;
    }
    else {
        *error = true;
    }

    return dont_read;
}

static bool increase_number(uint64_t *arg, int digit) {
    *arg *= (uint64_t)10;
    *arg += (uint64_t)digit;

    if (*arg > UINT32_MAX)
        return false;
    else
        return true;
}

static bool increase_correct_number(uint64_t *arg1, uint64_t *arg2,
                                    uint64_t *arg3, uint64_t *arg4,
                                    int *number_count, int digit) {
    switch (*number_count) {
    case 1:
        return increase_number(arg1, digit);
        break;
    case 2:
        return increase_number(arg2, digit);
        break;
    case 3:
        return increase_number(arg3, digit);
        break;
    case 4:
        return increase_number(arg4, digit);
        break;
    default:
        return false;
    }
}
bool read_command(char *type, uint64_t *arg1, uint64_t *arg2, uint64_t *arg3,
                  uint64_t *arg4, int *number_count) {
    bool return_value = true, ignore = false, error = false;
    int c;
    *arg1 = 0, *arg2 = 0, *arg3 = 0, *arg4 = 0, *number_count = 0;

    if (read_first_char(type, &return_value, &ignore, &error)) {
        if (error)
            *number_count = ERROR;

        if (ignore)
            *number_count = IGNORE;

        return return_value;
    }

    int white_space_count = 0;
    while (true) {
        c = getchar();

        if (c == '\n')
            break;

        if (c == EOF) {
            return_value = false;
            error = true;
            break;
        }

        if (is_white_char(c)) {
            white_space_count++;
        }
        else if (!is_digit(c) ||
                 (white_space_count == 0 && *number_count == 0)) {
            error = true;
        }
        else {
            if (white_space_count > 0) {
                (*number_count)++;
                white_space_count = 0;
            }

            if (!increase_correct_number(arg1, arg2, arg3, arg4, number_count,
                                         c - '0'))
                error = true;
        }
    }

    if (error)
        *number_count = ERROR;

    if (ignore)
        *number_count = IGNORE;

    return return_value;
}

char get_char_raw() {
    system("stty raw");
    int c = getchar();
    system("stty cooked");
    move_left();
    return c;
}

// int main() {
//     char type;
//     uint64_t arg1 = 0, arg2 = 0, arg3 = 0, arg4 = 0;
//     int number_count = 0;

//     while (read_command(&type, &arg1, &arg2, &arg3, &arg4, &number_count)) {
//         printf("%c %ld %ld %ld %ld %d \n", type, arg1, arg2, arg3, arg4,
//                number_count);
//         arg1 = 0, arg2 = 0, arg3 = 0, arg4 = 0;
//         number_count = 0;
//     }
// }