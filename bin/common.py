#!/bin/python3

import platform
import os
import sys
import argparse
import multiprocessing

debugMode = False
targetDir = None
rootPath = None
binaryPath = None

def printn(*args):
    sys.stdout.write(*args)

def isPlatform64():
    return "_64" in platform.machine()

def sanityCheck():
    printn("Sanity check... ")
    if not "GENGINE" in os.environ:
        print("GENGINE environment variable is not set.")
        exit(1)
    print("Ok!")

def init():
    global binaryPath
    global debugMode
    global targetDir
    global rootPath
    parser = argparse.ArgumentParser()
    parser.add_argument('-d', help='Debug mode', default=False, action='store_true')
    parser.add_argument('dir', help='Target directory', default='.', nargs='?')
    args = parser.parse_args()
    debugMode = args.d
    targetDir = os.getcwd() + "/" + args.dir + "/"
    rootPath = os.environ['GENGINE']
    binaryPath = rootPath + "/build/gengine" + ('d' if debugMode else '')

def build(emscripten=False):
    current_dir = os.getcwd()
    config = ('debug' if debugMode else 'release') + ('emscripten' if emscripten else '') + ('64' if isPlatform64() else '32')
    os.chdir(os.environ['GENGINE']+"/build")
    os.system("premake4 gmake")
    os.system(('emmake ' if emscripten else '') + "make config=" + config + " -j" + str(multiprocessing.cpu_count()))
    os.chdir(current_dir)

def run():
    os.system("LD_LIBRARY_PATH=" + rootPath + "/deps/linux/lib" + ('64' if isPlatform64() else '32') + " " + rootPath + "/build/gengine" + ('d' if debugMode else ''))

def packHtml():
    current_dir = os.getcwd()
    basename = os.path.basename(os.path.normpath(targetDir))
    os.chdir(os.environ['GENGINE']+"/build")
    os.system("emcc gengine" + ('d' if debugMode else '') + ".bc -o " + targetDir + "/" + basename + ".html --preload-file " + targetDir + "@")
    os.chdir(current_dir)

