
import json


with open("snippets.json.code-snippets","w") as json_file:
    snippets_base = {
        "C++ Competitive Programming Template": {
            "prefix": "cp_setup",
            "description": "C++ Competitive Programming Template"
        }
    }

    with open("cp_template.cpp") as template:
        
        lines = [x.rstrip("\n") for x in template.readlines()] + [r"// python tester.py ${TM_FILENAME_BASE} input -v testpy.py"]
        snippets_base["C++ Competitive Programming Template"]["body"] = lines
        json_file.write(json.dumps(snippets_base, indent=4))



