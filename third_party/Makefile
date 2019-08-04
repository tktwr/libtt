DIRS="glfw \
glad \
glm \
eigen \
stb \
imgui \
nativefiledialog \
json11"

graph:
	@for-dir.sh "git graph -1" $(DIRS)

fetch:
	@for-dir.sh "git fetch" $(DIRS)

status:
	@for-dir.sh "git status -s" $(DIRS)

tags:
	ctags -f tags.opencv2 -R opencv-4.1.0/build/include/opencv2
	ctags -f tags.glm -R glm/glm
	ctags -f tags.eigen -R eigen
	ctags -f tags.stb -R stb
	ctags -f tags.imgui -R imgui
	ctags -f tags.nativefiledialog -R nativefiledialog/src
	ctags -f tags.json11 -R json11
	ctags -f - -R /c/msys64/mingw64/x86_64-w64-mingw32/include | sed 's+C:/msys64+/c/msys64+' > tags.win

clone:
	git clone https://github.com/glfw/glfw.git
	git clone https://github.com/Dav1dde/glad.git
	git clone https://github.com/g-truc/glm.git
	git clone https://github.com/eigenteam/eigen-git-mirror.git eigen
	git clone https://github.com/nothings/stb.git
	git clone https://github.com/ocornut/imgui.git
	git clone https://github.com/mlabbe/nativefiledialog.git
	git clone https://github.com/dropbox/json11.git

clone-opt:
	git clone https://github.com/tanakh/cmdline.git
	git clone https://github.com/gabime/spdlog.git
	git clone https://github.com/USCiLab/cereal.git
	git clone https://github.com/kazuho/picojson.git

