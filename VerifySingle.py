import sys, os, hashlib, subprocess

GENERATED_ASM_DIR = "./asm/generated/"
REFERENCE_ASM_DIR = "./asm/reference/"

TARGET_HASH_DIR = "./target/"
SOURCE_CHECK_DIR = "./compiled/"

def disassemble_shader(path):
    xsd_result = subprocess.run("xsd " + path, shell=True, capture_output=True)
    return xsd_result.stdout.decode()

name = os.path.basename(sys.argv[1])

if not (name.endswith(".vsh") or name.endswith(".psh")):
    print("Shader name must end in .vsh or .psh: " + name)
    sys.exit(1)

if not os.path.exists(TARGET_HASH_DIR + name):
    print("Target shader not found: " + TARGET_HASH_DIR + name)
    sys.exit(1)

if not os.path.exists(SOURCE_CHECK_DIR + name):
    print("Missing shader: " + name + "!")
    sys.exit(1)

with open(SOURCE_CHECK_DIR + name, "rb") as src:
    data = src.read()
    src_hash = hashlib.md5(data).hexdigest()

with open(TARGET_HASH_DIR + name, "rb") as target:
    data = target.read()
    target_hash = hashlib.md5(data).hexdigest()

if src_hash == target_hash:
    print("Matched: " + name + "!")
    sys.exit(0)

src_asm = disassemble_shader(SOURCE_CHECK_DIR + name)
dst_asm = disassemble_shader(TARGET_HASH_DIR + name)

with open(GENERATED_ASM_DIR + name + ".asm", "w") as gen:
    gen.write(src_asm)

print(f"Failed to match: {name}! (Target: {os.path.getsize(TARGET_HASH_DIR + name)} / Source: {os.path.getsize(SOURCE_CHECK_DIR + name)} / Diff: {os.path.getsize(SOURCE_CHECK_DIR + name) - os.path.getsize(TARGET_HASH_DIR + name)})")
sys.exit(1)