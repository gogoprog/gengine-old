#!/usr/bin/python3

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

def getDeps():
    log("Downloading dependencies...")
    if platform.system() == "Linux":
        directory = os.environ['GENGINE']+"/deps/linux/lib"+('64' if isPlatform64() else '32')
        os.chdir(directory)
        if not os.path.isfile(directory+"/libcef.so"):
            os.system("./get-libs")

def build(emscripten=False):
    current_dir = os.getcwd()
    if not emscripten:
        getDeps()

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
    os.system("rm -rf out/*")
    basename = os.path.basename(os.path.normpath(targetDir))
    os.chdir(os.environ['GENGINE']+"/build")
    os.system("emcc " + ('' if debugMode else '-O3') + " --bind gengine" + ('d' if debugMode else '') + ".bc -o " + targetDir + "/" + basename + ".html --preload-file " + targetDir + "@ -s TOTAL_MEMORY=8388608 -s TOTAL_STACK=1048576 --shell-file " + rootPath + "/src/template.html")
    os.chdir(current_dir)
    os.system("mv " + basename + ".html index.html")
    os.system("cp -rf gui out/gui")
    os.system("mv *.js *.html *.data *.mem out/")
    if itMustRun:
        os.chdir(current_dir + "/out/")
        os.system("emrun " + basename + ".html")

