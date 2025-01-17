import os
import subprocess

Import('env')

platforms = ["arm", "x64", "esp"]


def ignorePlatformFiles(env, node):
    fileName = os.path.basename(str(node))
    platformFilter = env.GetProjectOption('custom_filter')
    if any(plat in fileName for plat in platforms):
        for plat in platforms:
            if plat in fileName and plat != platformFilter:
                print("Ignoring: " + str(node))
                return None
    print("Node: " + str(node))

    return node

env.AddBuildMiddleware(ignorePlatformFiles, "*")

def addVersionNumber(env, node):
    subprocess.call(["sh", "generateVersionHash.sh"])

env.AddBuildMiddleware(addVersionNumber, "main")