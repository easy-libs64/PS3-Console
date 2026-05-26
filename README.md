# PS3 Console

A lightweight console output utility for **PlayStation 3** homebrew applications using **PSL1GHT SDK** and TTF font rendering.

## Features

- **Ring buffer console**: Displays up to 10 lines of text with automatic circular overwrite
- **TTF font rendering**: Uses PS3 system font (SCE-PS3-SR-R-LATIN2.TTF) for crisp text display
- **Text and integer output**: Separate functions for string and integer printing
- **Customizable layout**: Configurable line height, font size, and screen offsets
- **White text on black background**: High-contrast rendering for easy readability

## Technical Details

| Aspect | Description |
|--------|-------------|
| Platform | PlayStation 3 (PPU) |
| SDK | PSL1GHT |
| Language | C |
| Font | SCE-PS3-SR-R-LATIN2.TTF (system font) |
| Font Size | 20×24 pixels (width×height) |
| Lines | 10 lines, 41 characters per line |
| Position | (100, 100) starting offset |

## Usage

```c
// Initialize console (load font, allocate buffers)
Console_INIT();

// Print text messages
Console_print("Hello, PS3!");

// Print integer values with prefix
Console_printInt("Frame: ", 7, fps);  // "Frame: 60"

// Render all lines to screen
Console_SHOW();

// Cleanup (free allocated memory)
Console_DeINIT();
```

## Dependencies

- [PSL1GHT SDK](https://github.com/ps3homebrew/PSL1GHT)
- `ttf_render.h` — TTF font rendering module
- `printF.h` — Helper print function

## API Reference

### Initialization

```c
void Console_INIT();      // Load font and allocate line buffers
void Console_SHOW();      // Render all lines to screen
void Console_DeINIT();    // Free all allocated memory
```

### Output Functions

```c
void Console_print(const char* msg);
// Copy string to current line, advance ring buffer

void Console_printInt(const char* msg, u32 msgSize, u32 num);
// Print message + integer (manual integer-to-string conversion)
```

## Configuration Constants

```c
#define MaxLineCount 10       // Maximum lines in ring buffer
#define MaxLineLen 41         // Characters per line (including null terminator)
#define HFONT 24              // Font height in pixels
#define WFONT 20              // Font width in pixels
#define XSTART 100            // Starting X position
#define YSTART 100            // Starting Y position
#define YOFFSET 6             // Vertical spacing between lines
```

## Color Macros

```c
#define WHITE (255 << 24) | (255 << 16) | (255 << 8) | 255
#define BLACK 0
```

## Purpose

Ideal for **debugging homebrew applications**, displaying runtime statistics (FPS, memory usage), or providing simple user feedback on PS3 hardware or in the **rpcs3** emulator.

## Notes

- Ring buffer automatically wraps when exceeding 10 lines
- Memory allocated for each line buffer (41 bytes × 10 lines)
- Ensure `Console_DeINIT()` is called to prevent memory leaks
