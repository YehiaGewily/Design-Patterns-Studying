import os
import re

ROOT_DIR = os.path.dirname(os.path.abspath(__file__))

HEADER_TEMPLATE = """/*
 * Design Patterns - {pattern_name}
 * Author: Yehya
 * Description: Implementation of the {pattern_name} pattern in C++.
 */
"""

ignored_dirs = {'.git', '.vs', 'out', 'build', '.idea', 'bin', 'obj'}

def get_pattern_name(filepath):
    filename = os.path.basename(filepath)
    name = os.path.splitext(filename)[0]
    # If filename is main, use parent dir name
    if name.lower() == 'main':
        return os.path.basename(os.path.dirname(filepath))
    return name.replace('_', ' ')

def process_file(filepath):
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    if "Author: Yehya" in content:
        return

    pattern_name = get_pattern_name(filepath)
    header = HEADER_TEMPLATE.format(pattern_name=pattern_name)
    
    # Prepend header
    new_content = header + "\n" + content
    
    # Write back
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(new_content)
    print(f"Updated {filepath}")

def generate_cmake_for_dir(directory):
    # specialized CMakeLists generation
    cpp_files = [f for f in os.listdir(directory) if f.endswith('.cpp')]
    subdirs = [d for d in os.listdir(directory) if os.path.isdir(os.path.join(directory, d)) and d not in ignored_dirs]
    
    if not cpp_files and not subdirs:
        return

    content = ""
    # Only add basic setup if it's not the root (root is already handled manually or we can overwrite it)
    # But this script runs on subdirectories mostly.
    
    # We will append to checks
    targets = []
    
    # Check if this directory seems to differ:
    # 1. Contains 'main.cpp' -> single executable?
    # 2. Contains multiple cpp files without main?
    
    has_main = 'main.cpp' in cpp_files
    
    if has_main:
        # If there is a main.cpp, assume all cpp files in this dir belong to one target
        dir_name = os.path.basename(directory)
        target_name = dir_name + "_Pattern"
        # Sanitize target name
        target_name = re.sub(r'[^a-zA-Z0-9_]', '_', target_name)
        
        srcs = " ".join(cpp_files)
        content += f"add_executable({target_name} {srcs})\n"
    else:
        # If no main.cpp, check if any other file likely has main
        # We'll read files to check for "int main"
        files_with_main = []
        lib_files = []
        for cpp in cpp_files:
            with open(os.path.join(directory, cpp), 'r', encoding='utf-8', errors='ignore') as f:
                content_txt = f.read()
                # support int main(), void main(), main()
                if re.search(r'\b(int|void)?\s*main\s*\(', content_txt, re.IGNORECASE):
                    files_with_main.append(cpp)
                else:
                    lib_files.append(cpp)
        
        # If we found files with main, create targets for them
        # If there are lib files, include them in ALL targets in this dir? 
        # Or maybe they are just standalone snippets?
        
        if len(files_with_main) > 0:
            for main_file in files_with_main:
                target_name = os.path.splitext(main_file)[0]
                target_name = re.sub(r'[^a-zA-Z0-9_]', '_', target_name)
                # Include lib files if any
                target_srcs = main_file + " " + " ".join(lib_files)
                content += f"add_executable({target_name} {target_srcs})\n"
        elif lib_files:
             # Just library code? maybe do nothing or create a library
             # For design patterns examples, usually they are runnable. 
             # Let's verify one of the "library" types earlier.
             pass

    # Process subdirs
    for d in subdirs:
        content += f"add_subdirectory({d})\n"
        generate_cmake_for_dir(os.path.join(directory, d))

    if content:
        cmake_path = os.path.join(directory, "CMakeLists.txt")
        # only write if not exists or if we match our signature?
        # we will overwrite to be sure
        with open(cmake_path, 'w', encoding='utf-8') as f:
            f.write(content)
        print(f"Generated CMakeLists.txt for {directory}")

def main():
    # 1. Rebrand
    for root, dirs, files in os.walk(ROOT_DIR):
        dirs[:] = [d for d in dirs if d not in ignored_dirs]
        for file in files:
            if file.endswith('.cpp') or file.endswith('.h'):
                process_file(os.path.join(root, file))
                
    # 2. CMake - Start from top subdirectories
    for cat in ['Behavioral', 'Creational', 'Structural', 'SOLID']:
        if os.path.exists(os.path.join(ROOT_DIR, cat)):
            generate_cmake_for_dir(os.path.join(ROOT_DIR, cat))

if __name__ == '__main__':
    main()
