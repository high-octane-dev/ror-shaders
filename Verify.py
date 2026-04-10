import os, hashlib, subprocess, math

DISASSEMBLE_SHADERS = False
GENERATED_ASM_DIR = "./asm/generated/"
REFERENCE_ASM_DIR = "./asm/reference/"

TARGET_HASH_DIR = "./target/"
SOURCE_CHECK_DIR = "./compiled/"

def disassemble_shader(path):
    xsd_result = subprocess.run("xsd " + path, shell=True, capture_output=True)
    return xsd_result.stdout.decode()

for file in os.listdir(GENERATED_ASM_DIR):
    os.remove(GENERATED_ASM_DIR + file)

files = os.listdir(TARGET_HASH_DIR)
match_count = 0
failed_matches = []
missing_shaders = []
for name in files:
    src_hash = None
    target_hash = None
    
    if not os.path.exists(SOURCE_CHECK_DIR + name):
        missing_shaders.append(name)
        continue
    
    with open(SOURCE_CHECK_DIR + name, "rb") as src:
        data = src.read()
        src_len = len(data)
        src_hash = hashlib.md5(data).hexdigest()
    
    with open(TARGET_HASH_DIR + name, "rb") as target:
        data = target.read()
        target_len = len(data)
        target_hash = hashlib.md5(data).hexdigest()

    if src_hash is not None and target_hash is not None:
        if src_hash != target_hash:
            src_asm = disassemble_shader(SOURCE_CHECK_DIR + name)
            dst_asm = disassemble_shader(TARGET_HASH_DIR + name)
            
            with open(GENERATED_ASM_DIR + name + ".asm", "w") as gen:
                gen.write(src_asm)
            failed_matches.append(name)
        else:
            match_count += 1
            print("Matched: " + name + "!")
            pass
    else:
        print("Failed to compute hashes for shader: " + name)

for name in failed_matches:
    if name.endswith(".vsh"):
        print("Failed to match: " + name + "! (" + str(os.path.getsize(TARGET_HASH_DIR + name)) + "B)")
    else:
        print("Failed to match: " + name + "!")
for name in missing_shaders:
    print("Missing shader: " + name + "!")

percent_matched = int(math.floor(match_count / len(files) * 100))
print("Matched: " + str(match_count) + " out of " + str(len(files)) + " Shaders! (" + str(percent_matched) + "%)")