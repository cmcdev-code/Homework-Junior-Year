def compare_files(file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        for line_num, (line1, line2) in enumerate(zip(f1, f2), start=1):
            # Remove whitespace, tabs, and newlines before comparison
            line1_stripped = line1.strip()
            line2_stripped = line2.strip()

            # Check if the lines are different after stripping whitespace
            if line1_stripped != line2_stripped:
                print(f"Difference found at line {line_num}:")
                print(f"File 1: {line1_stripped}")
                print(f"File 2: {line2_stripped}")

                # Print the specific differences between the lines
                for i, (char1, char2) in enumerate(zip(line1_stripped, line2_stripped), start=1):
                    if char1 != char2:
                        print(f"Difference at position {i}: '{char1}' vs '{char2}'")
                return  # Stop comparing as soon as a difference is found

    print("Files are the same.")

if __name__ == "__main__":
    file1 = input("Enter the path to the first file: ")
    file2 = input("Enter the path to the second file: ")
    compare_files(file1, file2)
