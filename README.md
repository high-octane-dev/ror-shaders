# Cars: Race-O-Rama Shaders

A shader decompilation project for **Cars: Race-O-Rama** (Xbox 360).

## Overview

This repository aims to decompile the Xenos shaders used in the Xbox 360 version of Cars: Race-O-Rama back into HLSL source code that matches 1:1 with the original game's logic. The shaders are compiled using the Xbox 360 version of the `fxc` shader compiler found in XDK 8276, to match the exact version used by the original developers. This project aims to produce byte-matching `.vsh` and `.psh` files.

The reason why this project exists is so that these shaders can later be refactored to work on Windows and ported into the PC version of Cars: Mater-National Championship, as currently, there are numerous  issues with the way scenes ported from Cars: Race-O-Rama appear visually. Understanding the way this game's shaders work will help tremendously with modding Cars: Mater-National Championship.

```
- source/          # Contains the HLSL source files.
- compiled/        # Contains the compiled versions of the source .hlsl shaders in `.vsh`/`.psh` format.
- target/          # Contains the original game's target .vsh/.psh binaries.
- asm/generated/   # Dissasembly output for the non-matching shaders in compiled/.
- asm/reference/   # Dissasembly output for the originial games' shaders in target/.
- CompileAll.py    # Script to automatically compile all shaders in the source/ folder and output them to the compiled/ folder.
- Verify.py        # Script to automatically identify matched shaders and dump dissassembly output to asm/generated/ and asm/reference/ as needed.
```

# Workflow

To decompile a shader, a specific `.vsh`/`.psh` file is chosen from the `target` folder, and it's .hlsl source file inside the `source/` folder is modified and permuted until it matches the target binary after `CompileAll.py` is ran. More specifically:
- 1. Run `Verify.py` to gauge current progress and find a shader to decompile that isn't missing.
- 2. Find that shader's `.hlsl` file in `source/`, and the target assembly in `asm/reference/`.
- 3. Analyze the reference assembly and recover the original logic, then transplant it into the `.hlsl` file.
- 4. Run `CompileAll.py`, or manually compile the shader with `fxc-xbox-8276` (with the proper arguments as outlined in `CompileAll.py`), then run `Verify.py` to check the results.
- 5. If the shader is now matched, you're done. If not, check the generated assembly in `asm/generated/` and compare it against the target `asm/reference/`, permute the `.hlsl` source again, and repeat steps 3-5 until the shader is matched.

### Requirements

- The Xbox 360 version of `fxc`, from XDK 8276. (`fxc-xbox-8276`)
- The Xbox Shader Disassembler from XDK 8276. (`xsd`)
- Python 3.x

## Technical Details

### Shader Model

- **Vertex Shader Profile**: `vs_3_0`
- **Pixel Shader Profile**: `ps_3_0`
- **Platform**: Xbox 360/Xenos ATI GPU