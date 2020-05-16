#include "input.h"

#pragma GCC diagnostic ignored "-Wunused-result"

/**
 * Tablica przechowująca dopuszczane białe znaki.
 */
static const int white_chars[] = {32, 9, 11, 12, 13};

/**
 * Stała przechowująca liczbę dopuszczanych białych znaków.
 */
static const int WHITE_COUNT = sizeof white_chars / sizeof(int);

/** @brief Sprawdza czy wczytany znak jest białym znakiem.
 * @param[in] x        – wczytany znak
 * @return Wartość @p true jeśli wczytany znak jest białym znakiem,
 * wartość @p false w przeciwnym przypadku.
 */
static bool is_white_char(int x) {
    for (int i = 0; i < WHITE_COUNT; i++)
        if (x == white_chars[i])
            return true;

    return false;
}

/** @brief Sprawdza czy wczytany znak jest literą.
 * @param[in] c        – wczytany znak
 * @return Wartość @p true jeśli wczytany znak jest literą,
 * wartość @p false w przeciwnym przypadku.
 */
static bool is_letter(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/** @brief Sprawdza czy wczytany znak jest cyfrą.
 * @param[in] x        – wczytany znak
 * @return Wartość @p true jeśli wczytany znak jest cyfrą,
 * wartość @p false w przeciwnym przypadku.
 */
static bool is_digit(int c) {
    return c >= '0' && c <= '9';
}

/** @brief Wczytuje pierwszy znak z wiersza i częściowo go interpretuje.
 * Wczytuje pierwszy znak z wiersza i sprawdza czy jest on literą, znakiem końca
 * linii, początkiem komentarza lub znakiem końca pliku. Ustawia zmienne @p type
 * @p ignore , @p return_value i @p error na odpowiednie wartości w zależności
 * od wczytanego znaku.
 * @param[in,out] type –         zmienna, do której zostanie zapisany wczytany
 *                               znak jeśli jest on literą,
 * @param[in,out] return_value – zmienna, do której zostanie zapisana informacja
 *                               czy wczytano znak końca pliku,
 * @param[in,out] ignore       – zmienna, do której zostanie zapisana informacja
 *                               czy wczytany wiersz należy zignorować,
 * @param[in,out] error        – zmienna, do której zostanie zapisana informacja
 *                               czy wczytany wiersz rozpoczyna się błędnym
 *                               znakiem.
 * @return Wartość @p true jeśli wczytany znak jest ostatnim w danym wierszu,
 * @p false w przeciwnym przypadku.
 */
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

/** @brief Dopisuje cyfę na koniec liczby.
 * Zwiększa podaną liczbę o tyle o ile zwiększyłaby się ona po dopisaniu na jej
 * końcu podanej cyfry. Nie pozwala przekroczyć UINT32_MAX.
 * @param[in,out] arg – wskaźnik na zmienną przechowującą modyfikowaną
 *                      liczbę,
 * @param[in] digit   – dopisywana cyfra.
 * @return Wartość @p true jeśli udało się zwiększyć liczbę bez przekroczenia
 * limitu, @p false w przeciwnym przypadku.
 */
static bool increase_number(uint64_t *arg, int digit) {
    *arg *= (uint64_t)10;
    *arg += (uint64_t)digit;

    if (*arg > UINT32_MAX)
        return false;
    else
        return true;
}

/** @brief Dopisuje cyfę na koniec wskazanej z czterech podanych liczb.
 * Przyjmuje cztery liczby i większa wskazaną liczbę o tyle o ile zwiększyłaby
 * się ona po dopisaniu na jej końcu podanej cyfry. Nie pozwala przekroczyć
 * UINT32_MAX.
 * @param[in,out] arg1     – wskaźnik na zmienną przechowującą pierwszą
 *                           modyfikowaną liczbę,
 * @param[in,out] arg2     – wskaźnik na zmienną przechowującą drugą
 *                           modyfikowaną liczbę,
 * @param[in,out] arg3     – wskaźnik na zmienną przechowującą trzeciąą
 *                           modyfikowaną liczbę,
 * @param[in,out] arg4     – wskaźnik na zmienną przechowującą czwartą
 *                           modyfikowaną liczbę,
 * @param[in] number_count – nr liczby, którą należy zmodyfikować,
 * @param[in] digit        – dopisywana cyfra.
 * @return Wartość @p true jeśli udało się zwiększyć liczbę bez przekroczenia
 * limitu, @p false w przeciwnym przypadku.
 */
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
    system("stty -echo raw");
    int c = getchar();
    system("stty echo cooked");
    move_left();
    return c;
}