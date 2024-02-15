# Filename: execute_and_print.py

# Step 1: Read the original Python code from the text file
source_file_path = input()
with open(source_file_path, 'r') as file:
    original_code = file.read()

# Step 2: Append a command to print the original code
# Escape triple quotes to prevent syntax errors if they exist in the original code
escaped_code = original_code.replace('"""', '\\"""')
modified_code = original_code + f'\nprint("""{escaped_code}""")'

# Step 3: Write the modified code to a new Python file
modified_file_path = 'modified_code.py'
with open(modified_file_path, 'w') as file:
    file.write(modified_code)


exec(open(modified_file_path).read())

# Optional: Clean up by removing the modified file after execution
import os
os.remove(modified_file_path)
