from glob import glob
import os

Import('env')

filterPlatform = env.GetProjectOption('custom_filter')

print("Filter: " + filterPlatform)

# get the list of files to be moved
allPlatformFiles = glob('**/*_[esp|native]*.*')

# move all files to the platform specific folder
correctFiles = []
for file in allPlatformFiles:
    print("Moving file: " + file)
    os.rename(file, "platform_specific/" + file.split("/")[-1])
    if filterPlatform in file:
        correctFiles.append(file.split("/")[-1])


# move the platform specific file to the root
for file in correctFiles:
    print("Moving file: " + file)
    os.rename("platform_specific/" + file, file)