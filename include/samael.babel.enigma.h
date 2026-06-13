// ------------------------------------------------------------------------------------------------
// samael.babel.enigma.h - This is a C implementation of the Enigma machine, a cipher device
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
// 
// As a big fan and music lover, to make this Enigma Engine how I call it unique and special; I
// have integrated in every rotor at position 27 & 28 the initials of a famous musician from
// the club 27. Hints will be given at every rotor.
// ------------------------------------------------------------------------------------------------
// Author:  Patrik Eigenmann
// eMail:   p.eigenmann72@gmail.com
// GitHub:  https://github.com/PatrikEigenmann72/enigma
// ------------------------------------------------------------------------------------------------
// Change Log:
// Wed 2026-06-10 File created.                                                     Version: 00.01
// Wed 2026-06-10 Basic preprocessor directives added.                              Version: 00.02
// Wed 2026-06-10 Rotor implementation added.                                       Version: 00.03
// Wed 2026-06-10 Small-, Med-, and LargeRotor implementation added.                Version: 00.04
// Wed 2026-06-10 Introducing Rotor->type for better logging and diagnostics.       Version: 00.05
// ------------------------------------------------------------------------------------------------
#ifndef SAMAEL_BABEL_ENIGMA_H
#define SAMAEL_BABEL_ENIGMA_H

/**
 * The length of the rotor alphabet. The flexibility of having a configurable length allows for
 * different implementations and testing scenarios. If you want to add more character to the rotors.
 * just increase this value and then update the rotor alaphabets accordingly. The original Enigma
 * machine used a 26-character alphabet (A-Z), but this implementation includes additional characters
 * to accommodate a wider range of inputs, including lowercase letters, digits, and special characters.
 */
#define ROTOR_ALPHABET_LENGTH 63

#pragma region Rotor Implementation
/**
 * The Rotor structure represents a single rotor in the Enigma machine. Each rotor has a specific
 * wiring configuration that defines how input characters are transformed as they pass through the rotor.
 * The rotor also keeps track of the number of turns it has made, which affects the transformation
 * of characters. The setAlphabet function pointer allows for dynamic configuration of the rotor's
 * wiring, enabling different rotor types (small, medium, large) to be initialized with their
 * specific alphabets. This design allows for flexibility and modularity in the implementation of the
 * Enigma machine, making it easier to manage and extend the functionality of the rotors as needed.
 */
typedef struct Rotor {
    /**
     * Identifier string for the type of rotor. Used to label the rotor in logs, debug output,
     * and internal diagnostics. Keeps rotor-type references consistent across the implementation
     * without exposing additional types in the header.
     */
    const char *type;

    /**
     * The array representing the rotor's wiring configuration. Each index corresponds to a position
     * in the rotor, and the value at that index represents the character that is mapped to that
     * position. The specific configuration of this array determines how characters are transformed
     * as they pass through the rotor during encryption and decryption processes. 
     */
    char rotor[ROTOR_ALPHABET_LENGTH];

    /**
     * The number of turns the rotor has made. This is important for implementing the stepping
     * mechanism of the Enigma machine, where rotors turn after a certain number of rotations,
     * affecting the transformation of characters as they pass through the machine. Keeping
     * track of the number of turns allows the Enigma engine to determine when to turn subsequent
     * rotors, which is a key aspect of the machine's encryption and decryption processes.
     * The number of turns can also be used to reset the rotor to its initial state, ensuring that
     * the machine starts from a known state.
     */
    int turns;

    /**
     * A function pointer to set the alphabet of the rotor. This allows for different rotor types to have
     * their own specific wiring configurations. When initializing a rotor, you can assign this pointer
     * to a function that sets the rotor's alphabet according to the desired configuration (e.g., small, medium, large). This design promotes modularity and flexibility in the implementation of the En
     */
    void (*setAlphabet)(struct Rotor *self);
} Rotor;

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
void rotor_init(Rotor *r, void (*setAlphabet)(Rotor *));

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
int  rotor_indexOf(const Rotor *r, char c);

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
void rotor_turn(Rotor *r);

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
char rotor_charAt(const Rotor *r, int i);

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
void rotor_reset(Rotor *r);

#pragma endregion

#pragma region SmallRotor implementation
/**
 * Initializes a small rotor with its specific alphabet configuration. This function sets up the
 * wiring for a small rotor, which is one of the types of rotors used in the Enigma machine. The
 * specific alphabet configuration for the small rotor should be defined within this function,
 * ensuring that it transforms characters according to the intended design of the Enigma machine.
 * By calling this function during the initialization of a rotor, you can ensure that the rotor is
 * properly configured to perform its role in the encryption and decryption processes of the Enigma
 * machine.
 * @param r The rotor to initialize as a small rotor.
 */
void smallRotor_init(Rotor *r);
#pragma endregion

#pragma region MediumRotor implementation
/**
 * Initializes a medium rotor with its specific alphabet configuration. This function sets up the
 * wiring for a medium rotor, which is one of the types of rotors used in the Enigma machine. The
 * specific alphabet configuration for the medium rotor should be defined within this function,
 * ensuring that it transforms characters according to the intended design of the Enigma machine.
 * By calling this function during the initialization of a rotor, you can ensure that the rotor is
 * properly configured to perform its role in the encryption and decryption processes of the Enigma
 * machine.
 * @param r The rotor to initialize as a medium rotor.
 */
void medRotor_init(Rotor *r);
#pragma endregion

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
void largeRotor_init(Rotor *r);
#pragma endregion

#pragma region EnigmaEngine implementation
/**
 * The EnigmaEngine structure represents the core of the Enigma machine, containing three rotors:
 * small, medium, and large. Each rotor has its own specific wiring configuration that defines how
 * characters are transformed as they pass through the machine. The EnigmaEngine provides functions
 * for initialization, resetting, encrypting and decrypting characters, as well as encrypting and
 * decrypting full strings. This structure encapsulates the state and behavior of the Enigma machine,
 * allowing for modular and organized implementation of the encryption and decryption processes.
 */
typedef struct EnigmaEngine {
    Rotor sm;
    Rotor med;
    Rotor lg;
} EnigmaEngine;

/**
 * Initializes the Enigma engine by setting up the small, medium, and large rotors with their
 * specific wiring configurations. This function prepares the Enigma machine for encryption and
 * decryption operations by ensuring that all rotors are properly initialized and ready to be used.
 * By calling this function, you can ensure that the Enigma engine is in a known state before
 * starting any encryption or decryption tasks.
 * 
 * @param e The Enigma engine to initialize.
 */
void enigma_init(EnigmaEngine *e);

/**
 * Resets the Enigma engine to its initial state. This function sets the number of turns for all
 * rotors back to zero and reinitializes their wiring configurations by calling the setAlphabet
 * function. Resetting the engine is important for ensuring that the Enigma machine starts from a
 * known state before beginning encryption or decryption operations. By calling this function, you
 * can ensure that the transformations applied to characters are consistent and predictable, which
 * is essential for both encrypting and decrypting messages accurately.
 * 
 * @param e The Enigma engine to reset.
 */
void enigma_reset(EnigmaEngine *e);

/**
 * This function is the core cypher mechanism of the Enigma engine. It takes a single character as
 * input and processes it through the small, medium, and large rotors to produce an encrypted
 * character.
 * 
 * @param e The Enigma engine to use for encryption.
 * @param c The character to encrypt.
 * @return The encrypted character.
 */
char enigma_encryptChar(EnigmaEngine *e, char c);

/**
 * The decryption process of the Enigma engine is the reversed process of the encryption. This
 * function takes a single character as input and processes it through the large, medium, and small
 * rotors in reverse order to produce a decrypted character.
 * 
 * @param e The Enigma engine to use for decryption.
 * @param c The character to decrypt.
 * @return The decrypted character.
 */
char enigma_decryptChar(EnigmaEngine *e, char c);

/**
 * Encrypts a string using the Enigma engine.
 * @param e The Enigma engine to use for encryption.
 * @param input The string to encrypt.
 * @param output The buffer to store the encrypted string.
 */
void enigma_encrypt(EnigmaEngine *e, const char *input, char *output);

/**
 * Decrypts a string using the Enigma engine.
 * @param e The Enigma engine to use for decryption.
 * @param input The string to decrypt.
 * @param output The buffer to store the decrypted string.
 */
void enigma_decrypt(EnigmaEngine *e, const char *input, char *output);
#pragma endregion // EnigmaEngine implementation

#endif // SAMAEL_BABEL_ENIGMA_H