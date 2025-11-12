# Moonlight Mousefix

A small C application to automatically disable mouse acceleration when spawning new [Moonlight](https://moonlight-stream.org) sessions. Previously, other fixes suggested using registry edits that would not take effect until the user logs out and back in. Using pywinauto is an option, but this is slow and unreliable.

---

# Features
- Disables "Enhance Pointer Precision" by closing mouse properties and then setting system parameters for disabling "Enhance Pointer Precision"

---

# Usage
1. Compile the c code with your compiler of choice either on windows or linux
2. Place your compiled exe (moonlight-mousefix.exe or moonlight-mousefix_fast.exe) in any folder and add it to sunshine or nvidia geforce experience to load this (Nvidia GFE>Settings>Shield, make sure Gamestream is enabled and add the exe. I named mine "Desktop")
3. Connect to moonlight and select your app and enjoy :)

---

# Building from source
Requires either mingw-w64 if compiling on linux or any GCC compiler if compiling on windows

```bash
x86_64-w64-mingw32-gcc moonlight-mousefix.c -o moonlight-mousefix.exe -mwindows -Os -s
x86_64-w64-mingw32-gcc moonlight-mousefix_fast.c -o moonlight-mousefix_fast.exe -mwindows -Os -s
