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
itMustRun = False

def printn(*args):
    sys.stdout.write(*args)

def log(*args):
    sys.stdout.write("[gengine] ")
    print(*args)

def isPlatform64():
    return "_64" in platform.machine()

def sanityCheck():
    printn("Sanity check... ")
    if not "GENGINE" in os.environ:
        print("GENGINE environment variable is not set.")
        exit(1)
    print("Ok!")

def init():
    log("Init script...")

    global binaryPath
    global debugMode
    global targetDir
    global rootPath
    global itMustRun
    parser = argparse.ArgumentParser()
    parser.add_argument('-d', help='Debug mode', default=False, action='store_true')
    parser.add_argument('-r', help='It must run', default=False, action='store_true')
    parser.add_argument('dir', help='Target directory', default='.', nargs='?')
    args = parser.parse_args()
    debugMode = args.d
    itMustRun = args.r
    targetDir = os.getcwd() + "/" + args.dir + "/"
    rootPath = os.environ['GENGINE']
    binaryPath = rootPath + "/build/gengine" + ('d' if debugMode else '')

def buildDeps():
    log("Building dependencies...")
    os.chdir(os.environ['GENGINE']+"/deps/common/libluasocket")
    config = 'release' + ('64' if isPlatform64() else '32')
    os.system("premake4 gmake")
    os.system("make config=" + config + " -j" + str(multiprocessing.cpu_count()))
    if platform.system() == "Linux":
        directory = os.environ['GENGINE']+"/deps/linux/lib"+('64' if isPlatform64() else '32')
        os.chdir(directory)
        if not os.path.isfile(directory+"/libcef.so"):
            os.system("./get-libs")

def build(emscripten=False):
    current_dir = os.getcwd()
    if not emscripten:
        buildDeps()

    log("Building gengine...")

    config = ('debug' if debugMode else 'release') + ('emscripten' if emscripten else '') + ('64' if isPlatform64() else '32')
    os.chdir(os.environ['GENGINE']+"/build")
    os.system("premake4 gmake")
    os.system(('emmake ' if emscripten else '') + "make config=" + config + " -j" + str(multiprocessing.cpu_count()))
    os.chdir(current_dir)

def run():
    os.system("LD_LIBRARY_PATH=" + rootPath + "/deps/linux/lib" + ('64' if isPlatform64() else '32') + " " + rootPath + "/build/gengine" + ('d' if debugMode else ''))

def packHtml():
    log("Packing html...")
    current_dir = os.getcwd()
    basename = os.path.basename(os.path.normpath(targetDir))
    os.chdir(os.environ['GENGINE']+"/build")
    os.system("emcc gengine" + ('d' if debugMode else '') + ".bc -o " + targetDir + "/" + basename + ".html --preload-file " + targetDir + "@ -s TOTAL_MEMORY=64000000")
    os.chdir(current_dir)

    if itMustRun:
        os.system("emrun " + basename + ".html")

