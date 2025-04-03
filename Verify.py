import os, hashlib, math

TARGET_HASH_DIR = "./target/"
SOURCE_CHECK_DIR = "./compiled/"

files = os.listdir(TARGET_HASH_DIR)
match_count = 0
for name in files:
    src_hash = None
    target_hash = None
    
    if not os.path.exists(SOURCE_CHECK_DIR + name):
        print("Missing shader: " + name)
        continue
    
    with open(SOURCE_CHECK_DIR + name, "rb") as src:
        src_hash = hashlib.md5(src.read()).hexdigest()
    
    with open(TARGET_HASH_DIR + name, "rb") as target:
        target_hash = hashlib.md5(target.read()).hexdigest()
    
    if src_hash is not None and target_hash is not None:
        if src_hash != target_hash:
            print("Failed to match: " + name + "!")
        else:
            match_count += 1
            print("Matched: " + name + "!")
            pass
    else:
        print("Failed to compute hashes for shader: " + name)
percent_matched = int(math.floor(match_count / len(files) * 100))
print("Matched: " + str(match_count) + " out of " + str(len(files)) + " Shaders! (" + str(percent_matched) + "%)")