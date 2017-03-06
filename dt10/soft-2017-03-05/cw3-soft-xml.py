import xml.etree.ElementTree as ET
import sys
import os

globalScope=ET.parse(sys.stdin)

import xml.dom.minidom

sys.stderr.write("\nDoing some basic checks.\n")

def check_variable(f):
    if "id" not in f.attrib:
        sys.stderr.write("\nWARNING: Variable element missing `id` attribute.")

def check_parameter(f):
    if "id" not in f.attrib:
        sys.stderr.write("\nWARNING: Parameter element missing `id` attribute.")


def check_scope(s):
    for child in s:
        if child.tag == "Scope":
            check_scope(child)
        elif child.tag=="Variable":
            check_variable(child)
        else:
            sys.stderr.write("\nWARNING: did not understand element {} as a child of {}".format(child.tag, s.tag))

def check_function(f):
    if "id" not in f.attrib:
        sys.stderr.write("\nWARNING: Function element missing `id` attribute.")
    for child in f:
        if child.tag == "Parameter":
            check_parameter(child)
        elif child.tag == "Scope":
            check_scope(child)
        else:
            sys.stderr.write("\nWARNING: did not understand element {} as a child of {}".format(child.tag, f.tag))


def check_program(p):
    if p.tag!="Program":
        sys.stderr.write("\nWARNING: top-level token is not `Program`")
    for child in p:
        if child.tag == "Function":
            check_function(child)
        elif child.tag == "Variable":
            check_variable(child)
        else:
            sys.stderr.write("\nWARNING: did not understand element {} as a child of {}".format(child.tag, p.tag))


check_program(globalScope.getroot())

sys.stderr.write("\nFinished checks.\n\n")


# Sigh. Let's have (more than) two ways of doing XML, and make them all broken
# in different aspects.
mini=xml.dom.minidom.parseString(ET.tostring(globalScope.getroot(), 'utf-8'))
pretty=mini.toprettyxml(indent='  ')
# http://stackoverflow.com/a/39984422
pretty = os.linesep.join([s for s in pretty.splitlines() if s.strip()])
sys.stdout.write(pretty)
sys.stdout.flush()
