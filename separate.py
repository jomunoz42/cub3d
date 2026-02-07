import re
import os
import sys

def split_c_functions(input_file):
    if not os.path.exists(input_file):
        print(f"Error: {input_file} not found.")
        return

    with open(input_file, 'r') as f:
        content = f.read()

    pattern = r'([\w\s\*]+\w+\s*\(.*?\)\s*\{[^{}]*(?:\{[^{}]*\}[^{}]*)*\})'
    
    functions = re.findall(pattern, content, re.DOTALL)
    
    if not functions:
        print(f"No functions found in {input_file}. Check the formatting!")
        return

    chunk_size = 5
    file_count = 0

    for i in range(0, len(functions), chunk_size):
        chunk = functions[i:i + chunk_size]
        file_name = f"vini_utils{file_count}.c"
        
        with open(file_name, 'w') as f:
            f.write("#include \"../headers/cub3d.h\"\n\n")
            cleaned_chunk = [fn.strip() for fn in chunk]
            f.write("\n\n".join(cleaned_chunk))
            f.write("\n")
            
        print(f"Created {file_name} with {len(chunk)} functions.")
        file_count += 1

if __name__ == "__main__":
    if len(sys.argv) > 1:
        split_c_functions(sys.argv[1])
    else:
        print("Usage: python separate.py <path_to_c_file>")