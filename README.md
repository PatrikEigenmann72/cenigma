# enigma

## About

### Usage

```
# Encryption of the the text "Hello Cryptography World!" and safe it in 'hello.eng'.
# File ending is completely up to you, there is no regulations if cipher text has
# to be in a file with a certain ending.
enigma -e "Hello Cryptography World!" > hello.eng

# Decryption of the file 'hello.eng' and safe it in hello.txt. Also here,
# there are no regulations that plaintext has to be in txt file. It is just
# common practice.
enigma -d hello.eng > hello.txt
```

### History and Context

This project implements a modern, software‑based interpretation of the Enigma machine — a cipher device developed and used in the early to mid‑20th century to protect commercial, diplomatic, and military communication. Enigma was deployed extensively by Nazi Germany during World War II, where it was trusted to secure the most sensitive and top‑secret messages.

In December 1932, Marian Rejewski of the Polish Cipher Bureau achieved the first major breakthrough against the plugboard‑equipped Enigma by applying permutation theory and exploiting operational weaknesses. His work, continued by Jerzy Różycki and Henryk Zygalski, laid the mathematical foundation for all subsequent Allied cryptanalysis.

On 26–27 July 1939, in Pyry near Warsaw, Polish intelligence shared their techniques, equipment, and reconstructed Enigma machines with French and British representatives. This act of cooperation became the starting point for the larger Allied cryptanalytic effort.

After the invasion of Poland, the Cipher Bureau staff escaped to Romania, destroyed their equipment to prevent capture, and eventually resumed cryptologic work in France. Their contributions continued quietly, often uncredited, but essential.

At Bletchley Park, Alan Turing and his colleagues expanded on the Polish foundations, developing new techniques and electromechanical devices to handle the enormous wartime traffic. Turing’s work was central not only to breaking Enigma but also to the birth of modern computing. After the war, he was prosecuted under discriminatory laws for his homosexuality, subjected to chemical castration, and died in 1954 under circumstances widely believed to be suicide. His treatment remains one of the most tragic injustices in the history of science and technology.

## Why do I exists

This software is not a replica of the historical Enigma.
It is a personal exploration — technical, historical, and emotional.

Rebuilding a rotor‑based cipher engine taught me more than how to design a reversible transformation or implement a stepping mechanism. It forced me to confront the human story behind the machine: the brilliance of the people who broke it, the cruelty of the systems that punished them, and the uncomfortable truth that technological progress does not automatically make us better human beings.

Turing’s fate is not an isolated historical footnote. It is a reminder that societies can celebrate genius while destroying the person who carries it. That realization disturbed me deeply — not as a programmer, but as a human being. It made me reflect on how little we have evolved in the ways that matter most. We still marginalize, exclude, and dehumanize people for their identity, orientation, language, appearance, or beliefs.

This project is my small way of acknowledging that history, honoring the people who shaped it, and refusing to let the human cost be forgotten.

### Personal Touch

Every rotor in this engine contains a subtle imprint: at positions 27 and 28, the initials of musicians from the “Club 27.” It’s a quiet tribute to artists whose brilliance burned intensely and briefly — another reminder of how fragile human lives are, and how often extraordinary people are lost too soon.

### What this tool is

Yes, it is a cipher engine.
Yes, it encrypts and decrypts text and files.
Yes, it is technically functional and practically useful.

But it is also a statement:

+ About history
+ About injustice
+ About the cost of brilliance
+ About the Responsibility we carry when we build things
+ About the need for a more humane future

This is not just a tool.
It is a reflection of why the tool exists.

## Folder Structure

The folders with binaries like executables, *.class - files, *.dll's will not be tracked.

```
enigma/
├── include/
│   ├── enigma.h
│   ├── samael.alchemy.manpage.h
│   ├── samael.alchemy.stringutility.h
│   ├── samael.babel.enigma.h
│   ├── samael.huginandmunin.debug.h
│   └── samael.huginandmunin.log.h
├── resources/
│   └── txt/
│   │   └── project.txt
├── scripts/
│   ├── compile.bat
│   ├── compile.ps1
│   ├── compile.sh
│   ├── get.bat
│   ├── get.ps1
│   ├── get.sh
│   ├── install.bat
│   ├── install.ps1
│   ├── install.sh
│   ├── new.bat
│   ├── new.ps1
│   ├── new.sh
│   ├── readme
│   ├── readme.bat
│   └── readme.ps1
├── src/
│   ├── enigma.c
│   ├── main.c
│   ├── samael.alchemy.manpage.c
│   ├── samael.alchemy.stringutility.c
│   ├── samael.babel.enigma.c
│   └── samael.huginandmunin.log.c
├── .gitignore
├── LICENSE
├── README.md
└── enigma.pmake
```

## Author

My name is Patrik Eigenmann. I learned to code when I was eight years old, long before it became my profession. Later I spent nine years as a software engineer, writing code because it was my job. When I moved into live sound, that obligation disappeared — but the curiosity stayed. I still write software because I want to understand things, not because someone assigns me a task. Coding keeps me sharp, and it gives me the freedom to explore ideas on my own terms.
I work on projects in my spare time, usually because something catches my interest or I want to figure out how something works under the hood. Nothing I build is backed by a team or a company. It’s just me, learning and creating because I enjoy it.
If you want to support my work, you can send a donation to p.eigenmann@gmx.net via PayPal. It’s optional, but appreciated.
Everything I publish is free under the GNU Public License v3.0. Use it, modify it, break it, rebuild it — whatever helps you learn or solve your own problems.

## Last Updated
Sun 2026-06-14
