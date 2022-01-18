#ifndef _DEV_H_
#define _DEV_H_

#define RESTORE "\033[0m"
#define RED "\033[01;31m"
#define GREEN "\033[01;32m"
#define YELLOW "\033[01;33m"
#define BLUE "\033[01;34m"
#define PURPLE "\033[01;35m"

#define log_str(str, colour) printf("%s%s%s", colour, str, RESTORE)
#define log_int(num, colour) printf("%s%d%s", colour, num, RESTORE)
#define log_double(num, colour) printf("%s%f%s", colour, num, RESTORE)

#define ece_world()                                                            \
    do {                                                                       \
        log_str("ECE ", YELLOW);                                               \
        log_int(420, GREEN);                                                   \
        log_str(" ", RESTORE);                                                 \
        log_str("world\n", BLUE);                                              \
    } while (0)

/*
Says hello (but with coloured text)
*/
#define say_hello()                                                            \
    do {                                                                       \
        log_str("Hello ", RED);                                                \
        ece_world();                                                           \
    } while (0)

/*
Prints the results
*/
#define print_result(size, time)                                               \
    do {                                                                       \
        log_str("For two matrices of size ", YELLOW);                          \
        log_int(size, GREEN);                                                  \
        log_str(",\nThe total time was: ", YELLOW);                            \
        log_double(time, GREEN);                                               \
        log_str(" seconds\n", YELLOW);                                         \
    } while (0)

/*
Draw ASCII Pepes
The calls have to be split up because of -Woverlength-strings
(509 character limitation on string literals)
*/
#define happy_pepe()                                                                                        \
    do {                                                                                                    \
        log_str("⣿⣿⣿⣿⣿⣿⠿⢋⣥⣴⣶⣶⣶⣬⣙⠻⠟⣋⣭⣭⣭⣭⡙⠻⣿⣿⣿⣿⣿\n" \
                "⣿⣿⣿⡿⢁⣾⣿⣿⣴⣿⣿⣿⣿⠿⠿⠷⠥⠱⣶⣶⣶⣶⡶⠮⠤⣌⡙⢿⣿\n" \
                "⣿⡿⢛⡁⣾⣿⣿⣿⡿⢟⡫⢕⣪⡭⠥⢭⣭⣉⡂⣉⡒⣤⡭⡉⠩⣥⣰⠂⠹\n" \
                "⡟⢠⣿⣱⣿⣿⣿⣏⣛⢲⣾⣿⠃⠄⠐⠈⣿⣿⣿⣿⣿⣿⠄⠁⠃⢸⣿⣿⡧\n",                                                          \
                GREEN);                                                                                     \
        log_str("⢠⣿⣿⣿⣿⣿⣿⣿⣿⣇⣊⠙⠳⠤⠤⠾⣟⠛⠍⣹⣛⣛⣢⣀⣠⣛⡯⢉⣰\n" \
                "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡶⠶⢒⣠⣼⣿⣿⣛⠻⠛⢛⣛⠉⣴⣿⣿\n" \
                "⣿⣿⣿⣿⣿⣿⣿⡿⢛⡛⢿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡈⢿⣿\n" \
                "⣿⣿⣿⣿⣿⣿⣿⠸⣿⡻⢷⣍⣛⠻⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢇⡘⣿\n",                                                          \
                GREEN);                                                                                     \
        log_str("⣿⣿⣿⣿⣿⣿⣿⣷⣝⠻⠶⣬⣍⣛⣛⠓⠶⠶⠶⠤⠬⠭⠤⠶⠶⠞⠛⣡⣿\n" \
                "⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣬⣭⣍⣙⣛⣛⣛⠛⠛⠛⠿⠿⠿⠛⣠⣿⣿\n" \
                "⣦⣈⠉⢛⠻⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⣁⣴⣾⣿⣿⣿⣿\n",                                                          \
                GREEN);                                                                                     \
    } while (0)

#define sad_pepe()                                                                                             \
    do {                                                                                                       \
        log_str("⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠋⠉⠉⠉⠙⠛⢿⠿⠛⠛⠛⠛⠛⠿⣿⣿⣿⣿⣿⣿\n" \
                "⣿⣿⣿⣿⣿⣿⡿⠁⠀⠀⢀⡀⠤⠤⢄⣀⠐⡄⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿\n" \
                "⣿⣿⣿⣿⣿⠟⠀⠀⠀⠐⠁⠀⠀⢀⣀⣀⣉⣒⣄⠉⠉⠉⢉⣀⣂⠈⠙⠻⣿⣿\n" \
                "⣿⣿⣿⠟⠉⡄⠀⠀⠀⠠⠤⣐⠭⠒⠉⠉⠉⠉⣒⣳⠈⠛⠂⠀⠀⣒⣛⡢⠈⢿\n",                                                            \
                GREEN);                                                                                        \
        log_str("⣿⣿⠁⠀⠀⠃⠀⠀⠈⠛⠛⠠⣤⣶⠖⠙⠀⡉⢻⡿⣶⣿⣿⠁⡂⠠⠈⢿⠗⢸\n" \
                "⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠂⠭⠤⠤⠤⣤⠄⠊⠀⠀⠈⠀⠀⠀⠀⢀⣶⣿\n" \
                "⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠒⠉⠀⠀⠀⠈⠁⠒⠂⠈⠁⠘⢿⣿⣿\n" \
                "⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿\n",                                                            \
                GREEN);                                                                                        \
        log_str("⡇⠀⠀⠀⠀⠀⠀⠀⠀⣾⣟⣛⣛⣻⡶⠶⠶⣶⣤⣤⣤⣤⣤⣤⣤⡶⠾⢃⣼⣿\n" \
                "⣷⡀⠀⠀⠀⠀⠀⠘⢄⡀⠀⠀⠉⠉⠙⠛⠛⠛⠓⠛⠻⠿⠿⠷⠿⠟⢃⣼⣿⣿\n" \
                "⣿⣿⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⣿⣿⣿⣿⣿\n",                                                            \
                GREEN);                                                                                        \
    } while (0)

/*
Says goodbye (but with coloured text)
*/
#define say_goodbye()                                                          \
    do {                                                                       \
        log_str("Goodbye ", RED);                                              \
        ece_world();                                                           \
    } while (0)

#endif
