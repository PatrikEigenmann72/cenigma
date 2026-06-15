// -------------------------------------------------------------------------------------------
// main.c - The heart of the software project. This is where the magic begins, and where the
// journey starts. For a C program, this is the entry point that brings everything together.
// It handles command-line arguments, manages the flow of execution, and coordinates the
// various components that make up the whole. This file is the central hub from which the
// program operates, ensuring that all parts work in harmony to achieve the desired
// functionality.
//
// Compile instructions:
// gcc/clang -DDEBUG -Wall -Wextra -I./include -o ./bin/enigma src/*.c    (debug build)
// gcc/clang -Wall -Wextra -I./include -o ./bin/enigma src/*.c            (release build)
// pmake enigma                                                           (release pmake build)
// pmake enigma -DDEBUG                                                   (debug pmake build)
// -------------------------------------------------------------------------------------------
// Author:  Patrik Eigenmann
// eMail:   p.eigenmann72@gmail.com
// GitHub:  https://github.com/PatrikEigenmann72/enigma
// -------------------------------------------------------------------------------------------
// Change Log:
// Mon 2026-06-01 File created.                                                 Version: 00.01
// Thu 2026-06-11 Added CLI functionality -e & -d.                              Version: 00.02
// Thu 2026-06-11 Added Manpage functionality.                                  Version: 00.03
// Sun 2026-06-14 Added debug and log outputs.                                  Version: 00.04
// -------------------------------------------------------------------------------------------

// Standard Library Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

// Samael Libraries Includes
#include "samael.babel.enigma.h"                    // My cypher engine "enigma".
#include "samael.huginandmunin.debug.h"             // Minimalist debugger header.
#include "samael.huginandmunin.log.h"               // Logging system header.

// enigma includes
#include "enigma.h"

/**
 * main - This function marks the beginning of execution for any C program. It serves as the
 * central coordinator, handling command-line arguments, initializing subsystems, and directing
 * the overall flow of the application. From here, the program invokes its core routines,
 * manages resources, and produces output. The main function embodies the universal convention
 * of C: every application, regardless of purpose or domain, begins its journey here.
 *
 * @param argc   The number of command-line arguments passed to the program.
 * @param argv   The array of command-line argument strings.
 * @return       EXIT_SUCCESS (0) on successful execution, or an error code otherwise.
 */
int main(int argc, char **argv) {

    log_init(LOG_ALL);

    const char *mode  = argv[1];
    const char *input = argv[2];

    debug_info("The %d command arguments are %s & %s", (argc - 1), mode, input);
    log_info("The %d command arguments are %s & %s", (argc - 1), mode, input);
    // ───────────────────────────────────────────────
    // 1. ENCRYPTION MODE (-e*)
    // ───────────────────────────────────────────────
    if (mode && strncmp(mode, "-e", 2) == 0) {

        debug_info("Entering the encryption routine.");
        log_info("Entering the encryption routine.");


        char output[65536];
        output[0] = '\0';
        debug_info("Allocating the output string and set it to '\\0'.");
        log_info("Allocating the output string and set it to '\\0'.");

        if (is_file(input)) {
            debug_info("Input is a file.");
            log_info("Input is a file.");
            
            enigma_encrypt_file(input, output);

            debug_info("Encryption of %s complete.", input);
            log_info("Encryption of %s complete.", input);
        } else {
            debug_info("Input is plaintext.");
            log_info("Input is plaintext.");
            
            enigma_encrypt_string(input, output);

            debug_info("Encryption of plaintext complete.");
            log_info("Encryption of plaintext complete.");
        }

        printf("%s", output);

        debug_info("Output the encrypted text.");
        log_info("Output the encrypted text.");

        return EXIT_SUCCESS;
    }

    // ───────────────────────────────────────────────
    // 2. DECRYPTION MODE (-d*)
    // ───────────────────────────────────────────────
    if (mode && strncmp(mode, "-d", 2) == 0) {

        debug_info("Entering the decryption routine.");
        log_info("Entering the decryption routine.");

        char output[65536];
        output[0] = '\0';

        debug_info("Allocating the output string and set it to '\\0'.");
        log_info("Allocating the output string and set it to '\\0'.");

        if (is_file(input)) {
            debug_info("Input is a file.");
            log_info("Input is a file.");

            enigma_decrypt_file(input, output);

            debug_info("Decryption of %s complete.", input);
            log_info("Decryption of %s complete.", input);
        } else {
            debug_info("Input is cipher text.");
            log_info("Input is cipher text.");

            enigma_decrypt_string(input, output);

            debug_info("Decryption of cipher text complete.");
            log_info("Decryption of cipher text complete.");
        }

        printf("%s", output);

        debug_info("Output the decrypted text.");
        log_info("Output the decrypted text.");

        return EXIT_SUCCESS;
    }

    // ───────────────────────────────────────────────
    // 3. INVALID MODE → MANPAGE (commented out)
    // ───────────────────────────────────────────────
    manpage_display();
    return EXIT_FAILURE;
}