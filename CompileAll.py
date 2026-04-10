import sys, os, subprocess, math, json, hashlib

IN_DIR = "./source/"
OUT_DIR = "./compiled/"
CACHE_FILE = "cache.json"

# Helper function to get the SHA-256 hash of a file
def get_file_hash(filepath):
    hasher = hashlib.sha256()
    try:
        with open(filepath, 'rb') as f:
            hasher.update(f.read())
        return hasher.hexdigest()
    except FileNotFoundError:
        return None

# Load the existing cache, or start fresh if it doesn't exist/is corrupted
if os.path.exists(CACHE_FILE):
    try:
        with open(CACHE_FILE, 'r') as f:
            cache = json.load(f)
    except json.JSONDecodeError:
        cache = {}
else:
    cache = {}

files = os.listdir(IN_DIR)
compiled_shaders = 0
total_shaders = 0

for i in range(len(files)):
    file = files[i]
    percent_complete = int(math.floor(i / len(files) * 100))
    
    if file.endswith(".hlsl"):
        total_shaders += 1
        source_path = IN_DIR + file
        vsh_file = OUT_DIR + file.replace(".hlsl", ".vsh")
        psh_file = OUT_DIR + file.replace(".hlsl", ".psh")
        
        # Check if file is in cache, hash matches, AND the output files still exist
        current_hash = get_file_hash(source_path)
        if (file in cache and cache[file] == current_hash and 
            os.path.exists(vsh_file) and os.path.exists(psh_file)):
            print("Skipped unchanged shader: " + file + " (" + str(percent_complete) + "%)")
            compiled_shaders += 1 # Count skipped as "compiled" for the final success message
            continue
            
        compiler = "fxc-xbox-8276"
        vertex_result = subprocess.run(compiler + " /XOautoz /Tvs_3_0 /Evs_main /Fo" + vsh_file + " " + source_path, shell=True, capture_output=True)
        pixel_result = subprocess.run(compiler + " /Tps_3_0 /Eps_main /Fo" + psh_file + " " + source_path, shell=True, capture_output=True)
    
        if vertex_result.returncode != 0 and pixel_result.returncode != 0:
            print("Failed to compile shader: " + file)
            print(compiler + " /XOautoz /Tvs_3_0 /Evs_main /Fo" + vsh_file + " " + source_path)
        elif vertex_result.returncode == 0 and pixel_result.returncode == 0:
            print("Successfully compiled shader: " + file + " (" + str(percent_complete) + "%)")
            compiled_shaders += 1
            # Update the cache only if compilation was entirely successful
            cache[file] = current_hash
        else:
            if vertex_result.returncode != 0:
                print("Failed to compile vertex shader: " + file)
            if pixel_result.returncode != 0:
                print("Failed to compile pixel shader: " + file)

# Save the updated cache back to disk
with open(CACHE_FILE, 'w') as f:
    json.dump(cache, f, indent=4)

if total_shaders == compiled_shaders:
    print("Compiled all shaders! ^w^")