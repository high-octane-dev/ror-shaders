import sys, os, hashlib

TARGET_HASH_DIR = "./target/"
SOURCE_CHECK_DIR = "./compiled/"

for name in os.listdir(TARGET_HASH_DIR):
    src_hash = None
    target_hash = None
    
    if not os.path.exists(SOURCE_CHECK_DIR + name):
        print("Missing shader: " + name)
        continue
    
    with open(SOURCE_CHECK_DIR + name, "rb") as src:
        src_hash = hashlib.md5(src.read()).hexdigest()
    
    with open(TARGET_HASH_DIR + name, "rb") as target:
        bytes = target.read()
        if b"2.0." in bytes:
            compiler_version = int(bytes[bytes.find(b"2.0.")+4:bytes.find(b"2.0.")+8].decode())
            #print("Shader: " + name + " Was built with: " + str(compiler_version))
        target_hash = hashlib.md5(bytes).hexdigest()
    
    if src_hash is not None and target_hash is not None:
        if src_hash != target_hash:
            print("Failed to match: " + name + "!")
        else:
            print("Matched: " + name + "!")
            pass
    else:
        print("Failed to compute hashes for shader: " + name)