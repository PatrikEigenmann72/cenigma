// ------------------------------------------------------------------------------------------------
// samael.babel.enigma.c - This is a C implementation of the Enigma machine, a cipher device
// developed and used in the early to mid‑20th century to protect commercial, diplomatic, and
// military communication. It was employed extensively by Nazi Germany during World War II, in all
// branches of the German military. The Enigma machine was considered so secure that it was used to
// encipher the most sensitive and top‑secret messages.
//
// Around December 1932, Marian Rejewski, a Polish mathematician and cryptologist at the Polish
// Cipher Bureau, used permutation theory and weaknesses in German operating procedures to break the
// daily message keys of the plugboard‑equipped Enigma. His work, along with that of Jerzy Różycki
// and Henryk Zygalski, laid the foundation for all subsequent Allied cryptanalysis of Enigma
// traffic.
//
// On 26 and 27 July 1939, in Pyry near Warsaw, Polish intelligence briefed French and British
// representatives on their Enigma‑decryption techniques and equipment, including Zygalski sheets
// and the early cryptologic bomb. They also provided each delegation with a Polish‑reconstructed
// Enigma machine. This cooperation became the starting point for the larger Allied cryptanalytic
// effort.
//
// In September 1939, British Military Mission 4, which included Colin Gubbins and Vera Atkins,
// traveled to Poland intending to evacuate the Polish cryptologists. By then, the Cipher Bureau
// staff had already been moved into Romania, destroying their equipment and records to prevent
// capture. From Romania they made their way to France, where they resumed cryptologic work and
// collaborated with the British via secure channels.
//
// At Bletchley Park, the British codebreaking center, Alan Turing and his colleagues expanded on
// the Polish foundations and developed new techniques and electromechanical devices to handle the
// vastly increased wartime traffic. Turing’s contributions were central to the success of the
// Enigma‑breaking effort and to the development of modern computing. After the war, however, he
// was prosecuted under discriminatory laws for his homosexuality, subjected to chemical castration,
// and died in 1954 under circumstances widely believed to be suicide. His treatment remains one
// of the most tragic injustices in the history of science and technology.
// ------------------------------------------------------------------------------------------------
// Author:  Patrik Eigenmann
// eMail:   p.eigenmann72@gmail.com
// GitHub:  https://github.com/PatrikEigenmann72/enigma
// ------------------------------------------------------------------------------------------------
// Change Log:
// Wed 2026-06-10 File created.                                                     Version: 00.01
// Wed 2026-06-10 Rotor functionality implemented.                                  Version: 00.02
// Wed 2026-06-10 LargeRotor implemented.                                           Version: 00.03
// Wed 2026-06-10 MediumRotor implemented.                                          Version: 00.04
// Wed 2026-06-10 SmallRotor implemented.                                           Version: 00.05
// Wed 2026-06-10 EnigmaEngine implemented.                                         Version: 00.06
// Wed 2026-06-10 samael.huginandmunin.debug.h implemented.                         Version: 00.07
// Wed 2026-06-10 Introducing Rotor->type for better logging and diagnostics.       Version: 00.08
// Wed 2026-06-10 Enhanced debug output for rotor operations.                       Version: 00.09
// ------------------------------------------------------------------------------------------------
#include "samael.babel.enigma.h"
#include "samael.huginandmunin.debug.h"
#include <string.h>

#pragma region Rotor Implementation

/**
 * Identifier string for the small rotor. Used to label the rotor in logs,
 * debug output, and internal diagnostics. Keeps rotor‑type references consistent
 * across the implementation without exposing additional types in the header.
 */
#define ROTOR_SMALL "small"

/**
 * Identifier string for the medium rotor. Used to label the rotor in logs,
 * debug output, and internal diagnostics. Keeps rotor‑type references consistent
 * across the implementation without exposing additional types in the header.
 */
#define ROTOR_MEDIUM "medium"

/**
 * Identifier string for the large rotor. Used to label the rotor in logs,
 * debug output, and internal diagnostics. Keeps rotor‑type references consistent
 * across the implementation without exposing additional types in the header.
 */
#define ROTOR_LARGE "large"

/**
 * The Rotor structure represents a single rotor in the Enigma machine. Each rotor has a specific
 * wiring configuration that defines how input characters are transformed as they pass through the rotor.
 * The rotor also keeps track of the number of turns it has made, which affects the transformation
 * of characters. The setAlphabet function pointer allows for dynamic configuration of the rotor's
 * wiring, enabling different rotor types (small, medium, large) to be initialized with their
 * specific alphabets. This design allows for flexibility and modularity in the implementation of the
 * Enigma machine, making it easier to manage and extend the functionality of the rotors as needed.
 * 
 * @param rotor The array representing the rotor's wiring configuration.
 * @param setAlphabet A function pointer to set the alphabet of the rotor, allowing for different
 *                    rotor types to have their own specific wiring configurations.
 */
void rotor_init(Rotor *r, void (*setAlphabet)(Rotor *)) {
    r->turns = 0;
    r->setAlphabet = setAlphabet;
    r->setAlphabet(r);
}

/**
 * Finds the index of a character in the rotor's alphabet. This function iterates through the
 * rotor's wiring configuration to locate the specified character. If the character is found,
 * its index is returned; otherwise, the function returns -1 to indicate that the character is
 * not present in the rotor's alphabet. This functionality is essential for both encryption and
 * decryption processes, as it allows the Enigma machine to determine how characters are
 * transformed as they pass through the rotors.
 * 
 * @param r The rotor to search.
 * @param c The character to find.
 * @return The index of the character, or -1 if not found.
 */
int rotor_indexOf(const Rotor *r, char c) {
    debug_verbose("Begin search for character '%c' in %s rotor...", c, r->type);
    for (int i = 0; i < ROTOR_ALPHABET_LENGTH; i++)
        if (r->rotor[i] == c) {
            debug_verbose("Character '%c' found at index %d", c, i);
            return i;
        }
    debug_err("Character '%c' not found in %s rotor", c, r->type);
    return -1;
}

/**
 * Turns the rotor by one position. This function simulates the mechanical rotation of the rotor,
 * which is a fundamental aspect of the Enigma machine's encryption and decryption processes. When
 * the rotor turns, the wiring configuration shifts, changing how characters are transformed as they
 * pass through the rotor. The number of turns is also incremented to keep track of the rotor's
 * position, which is crucial for implementing the stepping mechanism that causes subsequent rotors
 * to turn after a certain number of rotations.
 * 
 * @param r The rotor to turn.
 */
void rotor_turn(Rotor *r) {

    debug_verbose("Turning %s rotor, new turns: %d...", r->type, r->turns + 1);
    char first = r->rotor[0];    
    memmove(&r->rotor[0], &r->rotor[1], ROTOR_ALPHABET_LENGTH - 1);
    r->rotor[ROTOR_ALPHABET_LENGTH - 1] = first;
    r->turns++;
}

/**
 * Gets the character at a specific index in the rotor's alphabet. This function allows for
 * retrieving the character that corresponds to a given index in the rotor's wiring configuration.
 * It is used during both encryption and decryption processes to determine how characters are
 * transformed as they pass through the rotor. By providing the index, you can access the specific
 * character that the rotor maps to, which is essential for the correct functioning of the Enigma
 * machine.
 * 
 * @param r The rotor to query.
 * @param i The index of the character to retrieve.
 * @return The character at the specified index.
 */
char rotor_charAt(const Rotor *r, int i) {
    debug_verbose("Retrieving character at index %d from %s rotor...", i, r->type);
    return r->rotor[i];
}

/**
 * Resets the rotor to its initial state. This function sets the number of turns back to zero and
 * reinitializes the rotor's wiring configuration by calling the setAlphabet function. Resetting the
 * rotor is important for ensuring that the Enigma machine starts from a known state before beginning
 * encryption or decryption operations. By resetting the rotor, you can ensure that the
 * transformations applied to characters are consistent and predictable, which is essential for both
 * encrypting and decrypting messages accurately.
 * 
 * @param r The rotor to reset.
 */ 
void rotor_reset(Rotor *r) {
    debug_verbose("Resetting %s rotor...", r->type);
    r->turns = 0;
    r->setAlphabet(r);
}
#pragma endregion // Rotor Implementation

#pragma region SmallRotor implementation
/**
 * Initializes the small rotor with its specific alphabet configuration. This function sets up the
 * wiring for a small rotor, which is one of the types of rotors used in the Enigma enigine. The
 * specific alphabet configuration for the small rotor should be defined within this function,
 * ensuring that it transforms characters according to the intended design of the Enigma machine. By
 * calling this function during the initialization of a rotor, you can ensure that the rotor is
 * properly configured to perform its role in the encryption and decryption processes of the Enigma
 * machine.
 * 
 * At indices 26 and 27, this rotor carries a personal imprint: the initials of a musician from the
 * "Club 27" whose style and jazz influence helped shape modern rock music. The legacy of this artist,
 * reflects the small rotor's role as the fast, rhytmic driver of the mechanical engine.
 * 
 * @param r The rotor to initialize as a small rotor.
 */
static void smallRotor_setAlphabet(Rotor *self)
{
    debug_verbose("Setting alphabet for %s rotor...", self->type);
    int i = 0;

    self->rotor[i++] = ' '; self->rotor[i++] = 'E'; self->rotor[i++] = 'J'; self->rotor[i++] = 'O';
    self->rotor[i++] = 'T'; self->rotor[i++] = 'Y'; self->rotor[i++] = 'C'; self->rotor[i++] = 'H';
    self->rotor[i++] = 'M'; self->rotor[i++] = 'R'; self->rotor[i++] = 'e'; self->rotor[i++] = 'V';
    self->rotor[i++] = 'F'; self->rotor[i++] = 'K'; self->rotor[i++] = 'P'; self->rotor[i++] = 'U';
    self->rotor[i++] = 'Z'; self->rotor[i++] = 'D'; self->rotor[i++] = 'I'; self->rotor[i++] = 'N';
    self->rotor[i++] = 'S'; self->rotor[i++] = 'X'; self->rotor[i++] = 'B'; self->rotor[i++] = 'G';
    self->rotor[i++] = 'L'; self->rotor[i++] = 'Q';

    /* Club 27 imprint — Amy Winehouse (A, W) */
    self->rotor[i++] = 'A';
    self->rotor[i++] = 'W';

    self->rotor[i++] = 'j'; self->rotor[i++] = 'o'; self->rotor[i++] = 't'; self->rotor[i++] = 'y';
    self->rotor[i++] = 'c'; self->rotor[i++] = 'h'; self->rotor[i++] = 'm'; self->rotor[i++] = 'r';
    self->rotor[i++] = 'w'; self->rotor[i++] = 'a'; self->rotor[i++] = 'f'; self->rotor[i++] = 'k';
    self->rotor[i++] = 'p'; self->rotor[i++] = 'u'; self->rotor[i++] = 'z'; self->rotor[i++] = 'd';
    self->rotor[i++] = 'i'; self->rotor[i++] = 'n'; self->rotor[i++] = 's'; self->rotor[i++] = 'x';
    self->rotor[i++] = 'b'; self->rotor[i++] = 'g'; self->rotor[i++] = 'l'; self->rotor[i++] = 'q';
    self->rotor[i++] = 'v'; self->rotor[i++] = '0'; self->rotor[i++] = '1'; self->rotor[i++] = '2';
    self->rotor[i++] = '3'; self->rotor[i++] = '4'; self->rotor[i++] = '5'; self->rotor[i++] = '6';
    self->rotor[i++] = '7'; self->rotor[i++] = '8'; self->rotor[i++] = '9';

}

/**
 * Initializes the small rotor with its specific alphabet configuration. This function sets up the
 * wiring for a small rotor, which is one of the types of rotors used in the Enigma enigine. The
 * specific alphabet configuration for the small rotor should be defined within this function,
 * ensuring that it transforms characters according to the intended design of the Enigma machine.
 * By calling this function during the initialization of a rotor, you can ensure that the rotor is
 * properly configured to perform its role in the encryption and decryption processes of the Enigma
 * machine.
 * 
 * @param r The rotor to initialize as a small rotor.
 */
void smallRotor_init(Rotor *r)
{
    r->type = ROTOR_SMALL;
    debug_verbose("Initializing %s rotor...", r->type);
    rotor_init(r, smallRotor_setAlphabet);
}
#pragma endregion // SmallRotor implementation

#pragma region MediumRotor implementation
/**
 * Initializes a medium rotor with its specific alphabet configuration. This function sets up the
 * wiring for a medium rotor, which is one of the types of rotors used in the Enigma machine.
 * The specific alphabet configuration for the medium rotor should be defined within this function,
 * ensuring that it transforms characters according to the intended design of the Enigma machine. By
 * calling this function during the initialization of a rotor, you can ensure that the rotor is
 * properly configured to perform its role in the encryption and decryption processes of the Enigma
 * machine.
 * 
 * At indices 26 and 27, this rotor carries a personal imprint: the initials of a musician from the
 * “Club 27” whose raw, unpolished brilliance helped define the grunge movement. His influence mirrors
 * the rotor’s role as the engine’s transitional gear, sitting between the fast driver and the slow
 * mastermind.
 * 
 * @param r The rotor to initialize as a medium rotor.
 */
static void medRotor_setAlphabet(Rotor *self)
{
    debug_verbose("Setting alphabet for %s rotor...", self->type);
    int i = 0;

    self->rotor[i++] = '2'; self->rotor[i++] = ' '; self->rotor[i++] = '5'; self->rotor[i++] = 'E';
    self->rotor[i++] = 'J'; self->rotor[i++] = 'O'; self->rotor[i++] = 'T'; self->rotor[i++] = 'Y';
    self->rotor[i++] = 'L'; self->rotor[i++] = 'H'; self->rotor[i++] = '6'; self->rotor[i++] = 'M';
    self->rotor[i++] = 'R'; self->rotor[i++] = 'W'; self->rotor[i++] = 'A'; self->rotor[i++] = 'F';
    self->rotor[i++] = 'G'; self->rotor[i++] = 'P'; self->rotor[i++] = 'U'; self->rotor[i++] = 'Z';
    self->rotor[i++] = 'D'; self->rotor[i++] = 'I'; self->rotor[i++] = 'N'; self->rotor[i++] = 'S';
    self->rotor[i++] = 'X'; self->rotor[i++] = 'B';

    /* Club 27 imprint — Kurt Cobain (K, C) */
    self->rotor[i++] = 'K';
    self->rotor[i++] = 'C';

    self->rotor[i++] = 'Q'; self->rotor[i++] = 'V'; self->rotor[i++] = '9'; self->rotor[i++] = 'e';
    self->rotor[i++] = 'j'; self->rotor[i++] = 'o'; self->rotor[i++] = 't'; self->rotor[i++] = '8';
    self->rotor[i++] = '3'; self->rotor[i++] = 'y'; self->rotor[i++] = 'c'; self->rotor[i++] = 'h';
    self->rotor[i++] = '0'; self->rotor[i++] = 'm'; self->rotor[i++] = 'r'; self->rotor[i++] = 'w';
    self->rotor[i++] = 'a'; self->rotor[i++] = 'f'; self->rotor[i++] = 'k'; self->rotor[i++] = '7';
    self->rotor[i++] = 'p'; self->rotor[i++] = 'u'; self->rotor[i++] = 'z'; self->rotor[i++] = 'd';
    self->rotor[i++] = 'i'; self->rotor[i++] = '4'; self->rotor[i++] = 'n'; self->rotor[i++] = 's';
    self->rotor[i++] = 'x'; self->rotor[i++] = 'b'; self->rotor[i++] = 'g'; self->rotor[i++] = 'l';
    self->rotor[i++] = 'q'; self->rotor[i++] = 'v'; self->rotor[i++] = '1';

}

/**
 * Initializes a medium rotor with its specific alphabet configuration. This function sets up the
 * wiring for a medium rotor, which is one of the types of rotors used in the Enigma machine. The
 * specific alphabet configuration for the medium rotor should be defined within this function,
 * ensuring that it transforms characters according to the intended design of the Enigma machine.
 * By calling this function during the initialization of a rotor, you can ensure that the rotor is
 * properly configured to perform its role in the encryption and decryption processes of the Enigma
 * machine.
 *
 *  @param r The rotor to initialize as a medium rotor.
 */
void medRotor_init(Rotor *r)
{
    r->type = ROTOR_MEDIUM;
    debug_verbose("Initializing %s rotor...", r->type);
    rotor_init(r, medRotor_setAlphabet);
}
#pragma endregion // MediumRotor implementation

#pragma region LargeRotor implementation
/**
 * Initializes a large rotor with its specific alphabet configuration. This function sets up the
 * wiring for a large rotor, which is one of the types of rotors used in the Enigma machine. The
 * specific alphabet configuration for the large rotor should be defined within this function,
 * ensuring that it transforms characters according to the intended design of the Enigma machine.
 * By calling this function during the initialization of a rotor, you can ensure that the rotor is
 * properly configured to perform its role in the encryption and decryption processes of the Enigma
 * machine.
 * 
 * At indices 27 and 28, this rotor carries a personal imprint: the initials of a musician from the
 * “Club 27” whose influence on modern rock mirrors the rotor’s role as the engine’s slow, stabilizing
 * mastermind of pattern deflection.
 * 
 * @param r The rotor to initialize as a large rotor.
 */
static void largeRotor_setAlphabet(Rotor *self)
{
    debug_verbose("Setting alphabet for %s rotor...", self->type);
    int i = 0;

    self->rotor[i++] = '0'; self->rotor[i++] = '1'; self->rotor[i++] = ' '; self->rotor[i++] = 'B';
    self->rotor[i++] = '2'; self->rotor[i++] = 'b'; self->rotor[i++] = 'd'; self->rotor[i++] = 'f';
    self->rotor[i++] = 'h'; self->rotor[i++] = '3'; self->rotor[i++] = '4'; self->rotor[i++] = 'A';
    self->rotor[i++] = 'C'; self->rotor[i++] = 'E'; self->rotor[i++] = 'G'; self->rotor[i++] = '5';
    self->rotor[i++] = 'c'; self->rotor[i++] = 'e'; self->rotor[i++] = 'g'; self->rotor[i++] = 'i';
    self->rotor[i++] = '6'; self->rotor[i++] = 'U'; self->rotor[i++] = 'W'; self->rotor[i++] = 'Y';
    self->rotor[i++] = 'j'; self->rotor[i++] = 'l';

    /* Club 27 imprint — Jimi Hendrix (J, H) */
    self->rotor[i++] = 'J';
    self->rotor[i++] = 'H';

    self->rotor[i++] = '7'; self->rotor[i++] = '8'; self->rotor[i++] = '9'; self->rotor[i++] = 'D';
    self->rotor[i++] = 'F'; self->rotor[i++] = 'p'; self->rotor[i++] = 'n'; self->rotor[i++] = 'L';
    self->rotor[i++] = 'N'; self->rotor[i++] = 'P'; self->rotor[i++] = 'R'; self->rotor[i++] = 'T';
    self->rotor[i++] = 'V'; self->rotor[i++] = 'X'; self->rotor[i++] = 'Z'; self->rotor[i++] = 'I';
    self->rotor[i++] = 'K'; self->rotor[i++] = 'M'; self->rotor[i++] = 'O'; self->rotor[i++] = 'Q';
    self->rotor[i++] = 'S'; self->rotor[i++] = 'r'; self->rotor[i++] = 't'; self->rotor[i++] = 'v';
    self->rotor[i++] = 'x'; self->rotor[i++] = 'z'; self->rotor[i++] = 'a'; self->rotor[i++] = 'k';
    self->rotor[i++] = 'm'; self->rotor[i++] = 'o'; self->rotor[i++] = 'q'; self->rotor[i++] = 's';
    self->rotor[i++] = 'u'; self->rotor[i++] = 'w'; self->rotor[i++] = 'y';

}

/**
 * Initializes a large rotor with its specific alphabet configuration. This function sets up the
 * wiring for a large rotor, which is one of the types of rotors used in the Enigma machine. The
 * specific alphabet configuration for the large rotor should be defined within this function,
 * ensuring that it transforms characters according to the intended design of the Enigma machine.
 * By calling this function during the initialization of a rotor, you can ensure that the rotor is
 * properly configured to perform its role in the encryption and decryption processes of the Enigma
 * machine.
 *
 * @param r The rotor to initialize as a large rotor.
 */
void largeRotor_init(Rotor *r)
{
    r->type = ROTOR_LARGE;
    debug_verbose("Initializing %s rotor...", r->type);
    rotor_init(r, largeRotor_setAlphabet);
}
#pragma endregion // LargeRotor implementation

#pragma region EnigmaEngine implementation
/**
 * This function ensures that all the rotors in the enigma engine are reset to their initial state.
 * After calling this function the engine will be in a fresh state and ready for encryption or
 * decryption operations.
 * 
 * @param e The Enigma engine to reset.
 */
void enigma_init(EnigmaEngine *e)
{
    debug_verbose("Initializing Enigma engine...");
    smallRotor_init(&e->sm);
    medRotor_init(&e->med);
    largeRotor_init(&e->lg);
}

/**
 * This function ensures that all the rotors in the enigma engine are reset to their initial state.
 * After calling this function the engine will be in a fresh state and ready for encryption or
 * decryption operations. This particular function is useful for resetting the engine between
 * encryption and decryption tasks, ensuring a fresh start before processing new data.
 * 
 * @param e The Enigma engine to reset.
 */
void enigma_reset(EnigmaEngine *e)
{
    debug_verbose("Resetting Enigma engine...");
    rotor_reset(&e->sm);
    rotor_reset(&e->med);
    rotor_reset(&e->lg);
}

/**
 * This method advances the rotors according to the engine’s custom 27‑step cadence, ensuring that
 * each wheel turns in a rhythm independent of its alphabet size. It reproduces the mechanical
 * cascade of a physical rotor machine, where one rotor’s full cycle triggers the next. By decoupling
 * stepping from character count, it preserves reversibility while embedding the engine’s personal
 * “Club 27” timing signature.
 * 
 * @param e The Enigma engine containing the rotors to step.
 */
static void stepRotors(EnigmaEngine *e)
{
    debug_verbose("Stepping rotors...");
    /* Small rotor always turns */
    rotor_turn(&e->sm);

    debug_verbose("Small rotor turned. New first character: '%c'", e->sm.rotor[0]);
    /* Medium rotor turns every 27 small turns */
    if (e->sm.turns % 27 == 0) {
        rotor_turn(&e->med);

        debug_verbose("Medium rotor turned. New first character: '%c'", e->med.rotor[0]);
        /* Large rotor turns every 27 medium turns */
        if (e->med.turns % 27 == 0) {
            rotor_turn(&e->lg);
            debug_verbose("Large rotor turned. New first character: '%c'", e->lg.rotor[0]);
        }
    }
}

/**
 * Encrypts a single character using the Enigma engine. This function processes the input character
 * through the small, medium, and large rotors to produce an encrypted character. The function
 * first finds the index of the input character in the small rotor, then uses that index to
 * retrieve the corresponding character from the medium rotor, and finally finds the index of that
 * character in the large rotor to produce the final encrypted character. After processing the
 * character, the function calls stepRotors to advance the rotors according to the engine's stepping
 * mechanism. If the input character is not found in the small rotor, it is returned unchanged.
 * 
 * @param e The Enigma engine to use for encryption.
 */
char enigma_encryptChar(EnigmaEngine *e, char c)
{
    debug_verbose("Encrypting character '%c'...", c);
    int sindex = rotor_indexOf(&e->sm, c);
    if (sindex == -1) return c;
    debug_verbose("Found character '%c' at index %d in small rotor.", c, sindex);
    char mletter = rotor_charAt(&e->med, sindex);

    debug_verbose("Retrieved character '%c' from medium rotor.", mletter);
    int lindex = rotor_indexOf(&e->lg, mletter);
    debug_verbose("Found character '%c' at index %d in large rotor.", mletter, lindex);
    if (lindex == -1) return c;

    debug_verbose("Retrieving encrypted character from small rotor at index %d...", lindex);
    char encrypted = rotor_charAt(&e->sm, lindex);

    debug_verbose("Encrypted character: '%c'", encrypted);
    stepRotors(e);
    debug_verbose("Rotors stepped after encryption.");
    return encrypted;
}

/**
 * Decrypts a single character using the Enigma engine. This function processes the input character
 * through the large, medium, and small rotors to produce a decrypted character. The function
 * first finds the index of the input character in the small rotor, then uses that index to
 * retrieve the corresponding character from the medium rotor, and finally finds the index of that
 * character in the large rotor to produce the final decrypted character. After processing the
 * character, the function calls stepRotors to advance the rotors according to the engine's stepping
 * mechanism. If the input character is not found in the small rotor, it is returned unchanged.
 * 
 * @param e The Enigma engine to use for decryption.
 */
char enigma_decryptChar(EnigmaEngine *e, char c)
{
    debug_verbose("Decrypting character '%c'...", c);
    int lindex = rotor_indexOf(&e->sm, c);
    if (lindex == -1) return c;

    debug_verbose("Found character '%c' at index %d in small rotor.", c, lindex);
    char mletter = rotor_charAt(&e->lg, lindex);

    debug_verbose("Retrieved character '%c' from large rotor.", mletter);
    int sindex = rotor_indexOf(&e->med, mletter);
    debug_verbose("Found character '%c' at index %d in medium rotor.", mletter, sindex);
    if (sindex == -1) return c;

    debug_verbose("Retrieving decrypted character from small rotor at index %d...", sindex);
    char decrypted = rotor_charAt(&e->sm, sindex);

    debug_verbose("Decrypted character: '%c'", decrypted);
    stepRotors(e);

    debug_verbose("Rotors stepped after decryption.");
    return decrypted;
}

/**
 * Encrypts a string using the Enigma engine. This function takes an input string and processes each
 * character through the enigma_encryptChar function to produce an encrypted string. The function
 * first resets the Enigma engine to ensure a fresh state before starting the encryption process. It
 * then iterates through each character in the input string, encrypting it and storing the result in
 * the output buffer. Finally, it null-terminates the output string to ensure it is properly
 * formatted. This function allows for encrypting entire messages while maintaining the state of the
 * Enigma engine across characters, ensuring that the stepping mechanism is correctly applied
 * throughout the encryption process.
 * 
 * @param e The Enigma engine to use for encryption.
 * @param input The string to encrypt.
 * @param output The buffer to store the encrypted string.
 */
void enigma_encrypt(EnigmaEngine *e, const char *input, char *output)
{
    debug_verbose("Encrypting string: \"%s\"", input);
    enigma_reset(e);

    debug_verbose("Processing each character in the input string.");
    for (size_t i = 0; input[i] != '\0'; i++)
        output[i] = enigma_encryptChar(e, input[i]);

    debug_verbose("Encryption complete. Null-terminating output string.");
    output[strlen(input)] = '\0';
}

/**
 * Decrypts a string using the Enigma engine. This function takes an input string and processes each
 * character through the enigma_decryptChar function to produce a decrypted string. The function
 * first resets the Enigma engine to ensure a fresh state before starting the decryption process. It
 * then iterates through each character in the input string, decrypting it and storing the result in
 * the output buffer. Finally, it null-terminates the output string to ensure it is properly
 * formatted. This function allows for decrypting entire messages while maintaining the state of the
 * Enigma engine across characters, ensuring that the stepping mechanism is correctly applied
 * throughout the decryption process.
 * 
 * @param e The Enigma engine to use for decryption.
 * @param input The string to decrypt.
 * @param output The buffer to store the decrypted string.
 */
void enigma_decrypt(EnigmaEngine *e, const char *input, char *output)
{
    debug_verbose("Decrypting string: \"%s\"", input);
    enigma_reset(e);

    debug_verbose("Processing each character in the input string.");
    for (size_t i = 0; input[i] != '\0'; i++)
        output[i] = enigma_decryptChar(e, input[i]);

    debug_verbose("Decryption complete. Null-terminating output string.");
    output[strlen(input)] = '\0';
}
#pragma endregion // EnigmaEngine implementation