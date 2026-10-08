import sys, os, subprocess, json, hashlib

IN_DIR = "./source/"
OUT_DIR = "./compiled/"
CACHE_FILE = "cache.json"

def get_file_hash(filepath):
    hasher = hashlib.sha256()
    try:
        with open(filepath, 'rb') as f:
            hasher.update(f.read())
        return hasher.hexdigest()
    except FileNotFoundError:
        return None

file = sys.argv[1]
source_path = IN_DIR + file

if not os.path.exists(source_path):
    print("Source shader not found: " + source_path)
    sys.exit(1)

if os.path.exists(CACHE_FILE):
    try:
        with open(CACHE_FILE, 'r') as f:
            cache = json.load(f)
    except json.JSONDecodeError:
        cache = {}
else:
    cache = {}

vsh_file = OUT_DIR + file.replace(".hlsl", ".vsh")
psh_file = OUT_DIR + file.replace(".hlsl", ".psh")

current_hash = get_file_hash(source_path)
if (file in cache and cache[file] == current_hash and
    os.path.exists(vsh_file) and os.path.exists(psh_file)):
    print("Skipped unchanged shader: " + file)
    sys.exit(0)

compiler = "fxc-xbox-8276"
vertex_result = subprocess.run(compiler + " /XOautoz /Tvs_3_0 /Evs_main /Fo" + vsh_file + " " + source_path, shell=True, capture_output=True)
pixel_result = subprocess.run(compiler + " /Xbe:2- /Tps_3_0 /Eps_main /Fo" + psh_file + " " + source_path, shell=True, capture_output=True)

if vertex_result.returncode != 0 and pixel_result.returncode != 0:
    print("Failed to compile shader: " + file)
    print(compiler + " /XOautoz /Tvs_3_0 /Evs_main /Fo" + vsh_file + " " + source_path)
    sys.exit(1)
elif vertex_result.returncode == 0 and pixel_result.returncode == 0:
    print("Successfully compiled shader: " + file)
    cache[file] = current_hash
    with open(CACHE_FILE, 'w') as f:
        json.dump(cache, f, indent=4)
    sys.exit(0)
else:
    if vertex_result.returncode != 0:
        print("Failed to compile vertex shader: " + file)
    if pixel_result.returncode != 0:
        print("Failed to compile pixel shader: " + file)
    sys.exit(1)
