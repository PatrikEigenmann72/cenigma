// ------------------------------------------------------------------------------------------------
// enigma.c - This project implements a modern, software‑based interpretation of the Enigma machine
// — a cipher device developed and used in the early to mid‑20th century to protect commercial,
// diplomatic, and military communication. Enigma was deployed extensively by Nazi Germany during
// World War II, where it was trusted to secure the most sensitive and top‑secret messages.
//
// In December 1932, Marian Rejewski of the Polish Cipher Bureau achieved the first major
// breakthrough against the plugboard‑equipped Enigma by applying permutation theory and
// exploiting operational weaknesses. His work, continued by Jerzy Różycki and Henryk Zygalski,
// laid the mathematical foundation for all subsequent Allied cryptanalysis.
//
// On 26–27 July 1939, in Pyry near Warsaw, Polish intelligence shared their techniques, equipment,
// and reconstructed Enigma machines with French and British representatives. This act of
// cooperation became the starting point for the larger Allied cryptanalytic effort.
//
// After the invasion of Poland, the Cipher Bureau staff escaped to Romania, destroyed their
// equipment to prevent capture, and eventually resumed cryptologic work in France. Their
// contributions continued quietly, often uncredited, but essential.
//
// At Bletchley Park, Alan Turing and his colleagues expanded on the Polish foundations, developing
// new techniques and electromechanical devices to handle the enormous wartime traffic. Turing’s
// work was central not only to breaking Enigma but also to the birth of modern computing. After
// the war, he was prosecuted under discriminatory laws for his homosexuality, subjected to chemical
// castration, and died in 1954 under circumstances widely believed to be suicide. His treatment
// remains one of the most tragic injustices in the history of science and technology.
//
// WHY THIS PROJECT EXISTS
// -----------------------
// This software is not a replica of the historical Enigma. It is a personal exploration —
// technical, historical, and emotional. Rebuilding a rotor‑based cipher engine taught me
// more than how to design a reversible transformation or implement a stepping mechanism.
// It forced me to confront the human story behind the machine: the brilliance of the people who
// broke it, the cruelty of the systems that punished them, and the uncomfortable truth that
// technological progress does not automatically make us better human beings.
//
// Turing’s fate is not an isolated historical footnote. It is a reminder that societies can
// celebrate genius while destroying the person who carries it. That realization disturbed me
// deeply — not as a programmer, but as a human being. It made me reflect on how little we have
// evolved in the ways that matter most. We still marginalize, exclude, and dehumanize people
// for their identity, orientation, language, appearance, or beliefs.
//
// This project is my small way of acknowledging that history, honoring the people who shaped it,
// and refusing to let the human cost be forgotten.
//
// PERSONAL TOUCH
// --------------
// Every rotor in this engine contains a subtle imprint: at positions 27 and 28, the initials of
// musicians from the “Club 27.” It’s a quiet tribute to artists whose brilliance burned
// intensely and briefly — another reminder of how fragile human lives are, and how often
// extraordinary people are lost too soon.
//
// WHAT THIS TOOL IS
// -----------------
// Yes, it is a cipher engine.
// Yes, it encrypts and decrypts text and files.
// Yes, it is technically functional and practically useful.
// 
// But it is also a statement:
// 
// •  about history
// •  about injustice
// •  about the cost of brilliance
// •  about the responsibility we carry when we build things
// •  about the need for a more humane future
//
// This is not just a tool.
// It is a reflection of why the tool exists.
// ------------------------------------------------------------------------------------------------
// Author:  Patrik Eigenmann
// eMail:   p.eigenmann72@gmail.com
// GitHub:  https://github.com/PatrikEigenmann72/helloc
// ------------------------------------------------------------------------------------------------
// Change Log:
// Mon 2026-06-01 File created.                                                     Version: 00.01
// Wed 2026-06-10 Rotor functionality extracted into samael.babel.enigma.c.         Version: 00.02
// Wed 2026-06-10 LargeRotor extracted into samael.babel.enigma.c.                  Version: 00.03
// Wed 2026-06-10 MediumRotor extracted into samael.babel.enigma.c.                 Version: 00.04
// Wed 2026-06-10 SmallRotor extracted into samael.babel.enigma.c.                  Version: 00.05
// Wed 2026-06-10 EnigmaEngine extracted into samael.babel.enigma.c.                Version: 00.06
// Fri 2026-06-12 Manpage functionality implemented.                                Version: 00.07
// Mon 2026-06-15 Integrated debug & log information.                               Version: 00.08
// Mon 2026-06-15 Organized code by regions.                                        Version: 00.09
// ------------------------------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "enigma.h"

#include "samael.babel.enigma.h"
#include "samael.huginandmunin.debug.h"
#include "samael.huginandmunin.log.h"
#include "samael.alchemy.stringutility.h"
#include "samael.alchemy.manpage.h"

#pragma region Application Info
// ------------------------------------------------------------
// Identity constants (private to enigma)
// ------------------------------------------------------------
#define APP_NAME    "enigma"
#define MAJOR       0
#define MINOR       9

#define AUTHOR      "Patrik Eigenmann"
#define EMAIL       "p.eigenmann72@gmail.com"
#define GIT         "https://www.github.com/PatrikEigenmann72/pmake.git"
#define LICENSE     "GNU GPL 3.0"
#define BUILD_DATE  __DATE__
#pragma endregion

#pragma region Enigma functions
/**
 * Encrypting a string using the Enigma engine. This function takes an input string and processes
 * each character through the encryption mechanism of the Enigma engine, producing an encrypted
 * string. The function iterates through each character in the input string, encrypts it.
 * 
 * @param input The string to encrypt.
 * @param output The buffer to store the encrypted string.
 */
void enigma_encrypt_string(const char *input, char *output) {
    debug_info("Allocate the enigma engine.");
    log_info("Allocate the enigma engine.");
    EnigmaEngine eng;
    
    debug_info("Initialize the enigma engine.");
    log_info("Initialize the enigma engine.");
    enigma_init(&eng);
    
    debug_info("Encrypt the input string to a cipher.");
    log_info("Encrypt the input string to a cipher.");
    enigma_encrypt(&eng, input, output);
}

/**
 * Decrypting a string using the Enigma engine. This function takes an input string and processes
 * each character through the decryption mechanism of the Enigma engine, producing a decrypted
 * string. The function iterates through each character in the input string, decrypts it.
 * 
 * @param input The string to decrypt.
 * @param output The buffer to store the decrypted string.
 */
void enigma_decrypt_string(const char *input, char *output) {
    debug_info("Allocate the enigma engine.");
    log_info("Allocate the enigma engine.");
    EnigmaEngine eng;

    debug_info("Initialize the enigma engine.");
    log_info("Initialize the enigma engine.");
    enigma_init(&eng);

    debug_info("Decrypt the input cypher to plaintext.");
    log_info("Decrypt the input cypher to plaintext.");
    enigma_decrypt(&eng, input, output);
}

/**
 * Encrypts a file using the Enigma engine. This function reads the contents of the specified file,
 * processes each character through the encryption mechanism of the Enigma engine, and writes the
 * encrypted result back to the file or to a new file. This allows for encrypting entire
 * files while maintaining the state of the Enigma engine across characters, ensuring that the
 * stepping mechanism is correctly applied throughout the encryption process.
 * 
 * @param filename The name of the file to encrypt.
 * @param output The buffer to store the encrypted file contents.
 */
void enigma_encrypt_file(const char *filename, char *output) {

    debug_info("Reading file: %s.", filename);
    log_info("Reading file: %s.", filename);
    char *buffer = read_file(filename);

    if (!buffer) {
        debug_err("%s is not a file.", filename);
        log_err("%s is not a file.", filename);
        output[0] = '\0';
        return;
    }

    enigma_encrypt_string(buffer, output);

    debug_info("Free up the buffer.");
    log_info("Free up the buffer.");
    free(buffer);
}

/**
 * Decrypts a file using the Enigma engine. This function reads the contents of the specified file,
 * processes each character through the decryption mechanism of the Enigma engine, and writes the
 * decrypted result back to the file or to a new file.
 *
 * @param filename The name of the file to decrypt.
 * @param output The buffer to store the decrypted file contents.
 */
void enigma_decrypt_file(const char *filename, char *output) {

    debug_info("Reading file: %s.", filename);
    log_info("Reading file: %s.", filename);
    char *buffer = read_file(filename);
    
    if (!buffer) {
        debug_err("%s is not a file.", filename);
        log_err("%s is not a file.", filename);
        output[0] = '\0';
        return;
    }
    enigma_decrypt_string(buffer, output);

    debug_info("Free up the buffer.");
    log_info("Free up the buffer.");
    free(buffer);
}
#pragma endregion

#pragma region File functions
/**
 * Checks if the specified path is a file. This function is used to verify that the provided path
 * points to a valid file before attempting to read from or write to it. This is important
 * for ensuring that the Enigma engine can successfully access the file for encryption or decryption
 * operations. By checking if the path is a file, you can prevent errors and ensure that the Enigma
 * engine operates on valid input, which is essential for both encrypting and decrypting messages
 * accurately.
 * 
 * @param path The path to check.
 * @return 1 if the path is a file, 0 otherwise.
 */
int is_file(const char *path) {

    struct stat st;

    debug_info("Check %s.", path);
    log_info("Check %s.", path);
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

/**
 * Reads the entire contents of a file into a newly allocated buffer. The caller is responsible
 * for freeing the returned buffer.
 *
 * @param path The path of the file to read.
 * @return A pointer to a newly allocated buffer containing the file contents, or NULL on failure.
 */
char *read_file(const char *path) {

    debug_info("Read %s.", path);
    log_info("Read %s.", path);

    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buf = malloc(size + 1);
    if (!buf) {
        debug_err("File empty!");
        log_err("File empty!");
        fclose(f);
        return NULL;
    }

    fread(buf, 1, size, f);
    buf[size] = '\0';

    fclose(f);
    return buf;
}
#pragma endregion

#pragma region Manpage function
/**
 * manpage_display - Builds and displays the application's integrated manpage. This function
 * assembles all sections—name, synopsis, description, options, and license—into a complete help
 * page and delegates the final rendering to manpage_init(). The content is constructed dynamically
 * using append_format(), which keeps the layout flexible and easy to maintain.
 *
 * The design mirrors the UNIX manpage structure so developers and system administrators feel
 * immediately at home. This function is only invoked when help flags are detected, and its
 * output replaces normal program execution.
 *
 * @note Memory for all dynamically built sections is allocated here and freed before return.
 */
void manpage_display() {
    
    log_info("Assembling and displaying the manpage content.");
    debug_info("Assembling and displaying the manpage content.");
    
    int major = MAJOR;
    log_info("Setting major version to %02d.", major);
    debug_info("Setting major version to %02d.", major);
    
    int minor = MINOR;
    log_info("Setting minor version to %02d.", minor);
    debug_info("Setting minor version to %02d.", minor);

    // Define the filename of the manpage content
    char *name = NULL;
    log_info("Setting application name to NULL.");
    debug_info("Setting application name to NULL.");

    append_format(&name, APP_NAME);
    log_info("Appended application name: %s.", name);
    debug_info("Appended application name: %s.", name);

    char *synopsis = NULL;
    log_info("Setting synopsis to NULL.");
    debug_info("Setting synopsis to NULL.");

    append_format(&synopsis, "      enigma [ -e \"plaintext\" | filename ]\n");
    append_format(&synopsis, "      enigma [ -d \"ciphertext\" | filename ]\n");
    append_format(&synopsis, "      enigma [-h | -H | -help | -Help | -(\\)?]\n");
    log_info("Building synopsis: enigma [ -e \"plaintext\" | filename ] [ -d \"cyphertext\" | filename ] [-h | -H | -help | -Help | -(\\)?]");
    debug_info("Building synopsis: enigma [ -e \"plaintext\" | filename ] [ -d \"cyphertext\" | filename ] [-h | -H | -help | -Help | -(\\)?]");

    char *description = NULL;
    log_info("Setting description to NULL.");
    debug_info("Setting description to NULL.");

    append_format(&description, "      %s - This tool is a modern C implementation inspired by the Enigma \n", APP_NAME);
    append_format(&description, "      machine — the cipher device used throughout the early and mid - 20th \n");
    append_format(&description, "      century to secure commercial, diplomatic, and military communication. \n");
    append_format(&description, "      Enigma was deployed extensively by Nazi Germany during World War II and \n");
    append_format(&description, "      was trusted to protect the most sensitive messages.\n");
    append_format(&description, "\n");
    append_format(&description, "      The first major breakthroughs against Enigma came in 1932 from Polish \n");
    append_format(&description, "      cryptologists Marian Rejewski, Jerzy Różycki, and Henryk Zygalski, \n");
    append_format(&description, "      whose work laid the mathematical foundation for all later Allied \n");
    append_format(&description, "      cryptanalysis. In July 1939, Polish intelligence shared their methods \n");
    append_format(&description, "      and reconstructed machines with French and British representatives, \n");
    append_format(&description, "      enabling the larger wartime codebreaking effort.\n");
    append_format(&description, "\n");
    append_format(&description, "      At Bletchley Park, Alan Turing and his colleagues expanded on this \n");
    append_format(&description, "      foundation, developing new techniques and electromechanical systems \n");
    append_format(&description, "      to handle the enormous volume of encrypted traffic. Turings \n");
    append_format(&description, "      contributions were central to the success of the Enigma - breaking \n");
    append_format(&description, "      effort and to the birth of modern computing. His later persecution \n");
    append_format(&description, "      for his homosexuality — culminating in his death in 1954 — remains \n");
    append_format(&description, "      one of the most tragic injustices in the history of science.\n");
    append_format(&description, "\n");
    append_format(&description, "      This project is not a replica of the historical Enigma. It is a \n");
    append_format(&description, "      personal interpretation: a rotor-based cipher engine inspired by \n");
    append_format(&description, "      the mechanical principles of the original, but redesigned with a \n");
    append_format(&description, "      modern, extended alphabet and a unique stepping cadence. Each \n");
    append_format(&description, "      rotor includes a subtle tribute at positions 27 and 28 — the \n");
    append_format(&description, "      initials of musicians from the “Club 27,” a nod to brilliant \n");
    append_format(&description, "      lives cut short.\n");
    append_format(&description, "\n");
    append_format(&description, "      The purpose of this tool is both technical and human. Building it \n");
    append_format(&description, "      was an exploration of reversible cipher design, but also a \n");
    append_format(&description, "      confrontation with the history behind the machine: the brilliance of \n");
    append_format(&description, "      those who broke it, the cruelty of the systems that punished them, \n");
    append_format(&description, "      and the uncomfortable truth that technological progress does not \n");
    append_format(&description, "      guarantee moral progress. This project exists to honor that history \n");
    append_format(&description, "      and to acknowledge the human cost behind the mathematics.\n");

    log_info("Built description content.");
    debug_info("Built description content.");

    char *options = NULL;
    log_info("Setting options to NULL.");
    debug_info("Setting options to NULL");

    append_format(&options, "      -e [\"plaintext\" | file]\n");
    append_format(&options, "         Encrypts a quoted string or the full contents of a plaintext \n");
    append_format(&options, "         file. This is the forward path through the Enigma‑inspired \n");
    append_format(&options, "         engine. The result is emitted to stdout.\n");
    append_format(&options, "\n");
    append_format(&options, "      -d [\"ciphertext\" | file]\n");
    append_format(&options, "         Decrypts ciphertext created by this tool. Accepts inline \n");
    append_format(&options, "         encrypted text or a file containing it. The engine retraces \n");
    append_format(&options, "         the exact rotor sequence used during encryption and restores \n");
    append_format(&options, "         the original plaintext with full fidelity.\n");
    append_format(&options, "\n");
    append_format(&options, "      Output redirection:\n");
    append_format(&options, "         Use '>' to write the result to a file, or '>>' to append to an\n");
    append_format(&options, "         existing file. For example:\n");
    append_format(&options, "            enigma -e \"Hello\" > secret.txt\n");
    append_format(&options, "            enigma -d secret.txt >> log.txt\n");
    append_format(&options, "\n");
    append_format(&options, "      -h, -H, -help, -Help, \"-(\\)?\"\n");
    append_format(&options, "         Do you need help? Any of these flags will open the application's \n");
    append_format(&options, "         manpage. This UNIX-style help file, familiar to developers and \n");
    append_format(&options, "         system administrators, is integrated into enigma itself. The \n");
    append_format(&options, "         beauty of this approach is that anyone working on macOS, BSD, UNIX, \n");
    append_format(&options, "         or Linux will instantly feel at home with the layout. Think of it as \n");
    append_format(&options, "         your built-in guide whenever you need more insight into the program \n");
    append_format(&options, "         enigma.\n");
    log_info("Built options content.");
    debug_info("Built options content.");

    char *license = NULL;
    log_info("Setting license to NULL.");
    debug_info("Setting license to NULL.");

    append_format(&license, "      Copyright 2024 Free Software Foundation, Inc. License GPLv3+: GNU GPL version 3\n");
    append_format(&license, "      or later <https://gnu.org/licenses/gpl.html>. This is free software: you are free\n");
    append_format(&license, "      to change and redistribute it. There is NO WARRANTY, to the extent permitted by law.\n");
    log_info("Built license content.");
    debug_info("Built license content.");

    // Create the manpage in the file
    log_info("Initializing manpage with assembled content.");
    debug_info("Initializing manpage with assembled content.");
    manpage_init(major, minor, name, synopsis, description, options, license);

    // Free up the memory.
    free(name);             
    log_info("Freed memory allocated for name.");
    debug_info("Freed memory allocated for name.");
    
    free(synopsis);         
    log_info("Freed memory allocated for synopsis.");
    debug_info("Freed memory allocated for synopsis.");

    free(description);      
    log_info("Freed memory allocated for description.");
    debug_info("Freed memory allocated for description.");

    free(options);          
    log_info("Freed memory allocated for options.");
    debug_info("Freed memory allocated for options.");

    free(license);          
    log_info("Freed memory allocated for license.");
    debug_info("Freed memory allocated for license.");
}
#pragma endregion