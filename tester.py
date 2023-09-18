import sys
import subprocess

def run_program(executable, input_file):
    try:
        output = subprocess.check_output([executable], stdin=open(input_file), text=True)
        return output
    except subprocess.CalledProcessError as e:
        print(f"Error: {e}")
        return None

def verify_output(verifier_script, output):
    try:
        verifier_output = subprocess.check_output(["python", verifier_script], input=output, text=True)
        return verifier_output.strip()
    except subprocess.CalledProcessError as e:
        print(f"Verification failed: {e}")
        return None

def main():
    if len(sys.argv) < 3:
        print("Usage: python tester.py <executable_name> <input_file> [-v <verifier_script>]")
        return
    
    executable_name = sys.argv[1]
    input_file = sys.argv[2]
    
    verifier_script = None
    if "-v" in sys.argv:
        verifier_index = sys.argv.index("-v") + 1
        if verifier_index < len(sys.argv):
            verifier_script = sys.argv[verifier_index]
    
    output = run_program(executable_name, input_file)
    
    if output is not None:
        print("Program output:")
        print(output)
        
        if verifier_script is not None:
            verification_result = verify_output(verifier_script, output)
            if verification_result is not None:
                print("Verification result:")
                print(verification_result)
        
        with open("output","w") as file:
            file.write(output)

if __name__ == "__main__":
    main()
