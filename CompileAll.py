import sys, os, subprocess, math

IN_DIR = "./source/"
OUT_DIR = "./compiled/"

files = os.listdir(IN_DIR)
compiled_shaders = 0
total_shaders = 0
for i in range(len(files)):
    file = files[i]
    percent_complete = int(math.floor(i / len(files) * 100))
    if file.endswith(".hlsl"):
        total_shaders += 1
        vsh_file = OUT_DIR + file.replace(".hlsl", ".vsh")
        psh_file = OUT_DIR + file .replace(".hlsl", ".psh")
        
        compiler = "fxc-xbox-8276"
        vertex_result = subprocess.run(compiler + " /XOautoz /Tvs_3_0 /Evs_main /Fo" + vsh_file + " " + IN_DIR + file, shell=True, capture_output=True)
        pixel_result = subprocess.run(compiler + " /Tps_3_0 /Eps_main /Fo" + psh_file + " " + IN_DIR + file, shell=True, capture_output=True)
    
        if vertex_result.returncode != 0 and pixel_result.returncode != 0:
            print("Failed to compile shader: " + file)
        elif vertex_result.returncode == 0 and pixel_result.returncode == 0:
            print("Successfully compiled shader: " + file + " (" + str(percent_complete) + "%)")
            compiled_shaders += 1
        else:
            if vertex_result.returncode != 0:
                print("Failed to compile vertex shader: " + file)
            if pixel_result.returncode != 0:
                print("Failed to compile pixel shader: " + file)
if total_shaders == compiled_shaders:
    print("Compiled all shaders! ^w^")