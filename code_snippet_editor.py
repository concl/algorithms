
import json


snippets_base = json.load(open("snippets.code-snippets","r"))

with open("snippets.code-snippets","w") as json_file:

    snippets_base["C++ Competitive Programming Template"] = {"prefix": "cp_setup"}

    with open("cp_template.cpp") as template:
        
        lines = [x.rstrip("\n") for x in template.readlines()] + [r"// python tester.py ${TM_FILENAME_BASE} input -v testpy.py", r"// python3 tester.py ${TM_FILENAME_BASE} input -v testpy.py"]

        # add $0
        starting_point = lines.index(r"int main() {") + 4
        lines[starting_point] += "$0"

        # add snippets
        snippets_base["C++ Competitive Programming Template"]["body"] = lines
        json_file.write(json.dumps(snippets_base, indent=4))



