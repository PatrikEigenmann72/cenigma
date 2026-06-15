// ------------------------------------------------------------------------------------------------
// enigma.h - This project implements a modern, software‑based interpretation of the Enigma machine
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
// GitHub:  https://github.com/PatrikEigenmann72/enigma
// ------------------------------------------------------------------------------------------------
// Change Log:
// Mon 2026-06-01 File created.                                                     Version: 00.01
// Wed 2026-06-10 Begin extraction of the Enigma machine into samael.babel.enigma.  Version: 00.02
// Wed 2026-06-10 Rotor functionality extracted to samael.babel.enigma.             Version: 00.03
// Wed 2026-06-10 Small-, Med-, and LargeRotor extracted to samael.babel.enigma.    Version: 00.04
// Wed 2026-06-10 EnigmaEngine extracted to samael.babel.enigma.c                   Version: 00.05
// Thu 2026-06-11 CLI functionality added.                                          Version: 00.06
// Mon 2026-06-18 Organized file by regions.                                        Version: 00.07
// ------------------------------------------------------------------------------------------------
#ifndef ENIGMA_H
#define ENIGMA_H

#pragma region Cryptographic functions
/**
 * Encrypting a string using the Enigma engine. This function takes an input string and processes
 * each character through the encryption mechanism of the Enigma engine, producing an encrypted
 * string. The function iterates through each character in the input string, encrypts it.
 * 
 * @param input The string to encrypt.
 * @param output The buffer to store the encrypted string.
 */
void enigma_encrypt_string(const char *input, char *output);

/**
 * Decrypting a string using the Enigma engine. This function takes an input string and processes
 * each character through the decryption mechanism of the Enigma engine, producing a decrypted
 * string. The function iterates through each character in the input string, decrypts it.
 * 
 * @param input The string to decrypt.
 * @param output The buffer to store the decrypted string.
 */
void enigma_decrypt_string(const char *input, char *output);

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
void enigma_encrypt_file(const char *filename, char *output);

/**
 * Decrypts a file using the Enigma engine. This function reads the contents of the specified file,
 * processes each character through the decryption mechanism of the Enigma engine, and writes the
 * decrypted result back to the file or to a new file. This allows for decrypting entire
 * files while maintaining the state of the Enigma engine across characters, ensuring that the
 * stepping mechanism is correctly applied throughout the decryption process.
 * 
 * @param filename The name of the file to decrypt.
 * @param output The buffer to store the decrypted file contents.
 */
void enigma_decrypt_file(const char *filename, char *output);
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
int is_file(const char *path);

/**
 * Reads the entire contents of a file into a newly allocated buffer. This function is used by the
 * Enigma engine to load file contents before encryption or decryption. The caller is responsible
 * for freeing the returned buffer.
 * 
 * @param path The path of the file to read.
 * @return A pointer to a newly allocated buffer containing the file contents, or NULL on failure.
 */
char *read_file(const char *path);
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
 */
void manpage_display();
#pragma endregion

#endif