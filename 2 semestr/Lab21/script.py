import os
import shutil
homedir = os.getcwd()
if(not os.path.exists("copiedFiles")):
		os.mkdir("copiedFiles")
directorys = os.walk(homedir)

for directory in directorys:
	path = directory[0]
	for file in directory[2]:
		fullpath = os.path.join(path, file)
		if(not os.access(fullpath, os.W_OK)):
			newfullpath = os.path.join("copiedFiles/", "copied_"+file)
			shutil.copy(fullpath, "copiedFiles")
			os.rename(os.path.join("copiedFiles/", file), os.path.join("copiedFiles/", "copied_"+file))
			os.chmod(newfullpath, os.stat.S_IWUSR|os.stat.S_IWGRP|os.stat.S_IWOTH)