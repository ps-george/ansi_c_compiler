import json
import sys

keys=set(["Text","Class","StreamLine","SourceFile","SourceLine","SourceCol"])
classes=set(["Keyword","Identifier","Operator","Constant","StringLiteral","Invalid"])
        
tokens=json.load(sys.stdin)
print(json.dumps(tokens, sort_keys=True, indent=4))

sys.stderr.write("\nDoing some basic checks.\n")

if not isinstance(tokens,list):
    sys.stderr.write("Expected JSON to be an array at the top-level\n")

if len(tokens)>0 and isinstance(tokens[-1],dict) and len(tokens[-1])==0:
    sys.stderr.write("List is terminated with empty token (which is fine). Removing empty token.\n")
    del tokens[-1]

for t in tokens:
    if not isinstance(t,dict):
        sys.stderr.write("Expected token '{}' to be a dictionary.\n".format(t))
    else:
        for k in t:
            if k not in keys:
                sys.stderr.write("Warning: unknown key '{}'\n".format(k))
        if "Class" in t:
            if t[k] not in classes:
                sys.stderr.write("Warning: unknown class '{}'\n".format(t[k]))

sys.stderr.write("\nFinished checks.\n")
