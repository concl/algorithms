
import os
import json

path = os.path.dirname(os.path.abspath(__file__))
snippets = "snippets.code-snippets"
template = "cp_template.cpp"
clean_template = "clean_template.cpp"

try:
    snippets_base = json.load(open(os.path.join(path, snippets),"r"))
except:
    print("Snippets file isn't valid. Defaulting to empty dictionary.")
    snippets_base = {}
    

with open(os.path.join(path, snippets),"w") as json_file:

    snippets_base["C++ Competitive Programming Template"] = {"prefix": "cp_setup"}
    with open(os.path.join(path, template)) as template:
        
        lines = [x.rstrip("\n") for x in template.readlines()] + [r"// python tester.py ${TM_FILENAME_BASE} input -v testpy.py", r"// python3 tester.py ${TM_FILENAME_BASE} input -v testpy.py"]

        # add $0
        starting_point = lines.index(r"int main() {") + 4
        lines[starting_point] += "$0"

        # add snippets
        snippets_base["C++ Competitive Programming Template"]["body"] = lines
    
    snippets_base["Clean Template"] = {"prefix": "clean_setup"}
    with open(os.path.join(path, clean_template)) as template:
        
        lines = [x.rstrip("\n") for x in template.readlines()] + [r"// python tester.py ${TM_FILENAME_BASE} input -v testpy.py", r"// python3 tester.py ${TM_FILENAME_BASE} input -v testpy.py"]

        # add $0
        starting_point = lines.index(r"int main() {") + 4
        lines[starting_point] += "$0"

        # add snippets
        snippets_base["Clean Template"]["body"] = lines

    json_file.write(json.dumps(snippets_base, indent=4))
    



