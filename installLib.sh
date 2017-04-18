bin=~/bin

urlGlew="https://downloads.sourceforge.net/project/glew/glew/2.0.0/glew-2.0.0.zip?ts=1491410177"
urlGlfw=https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
urlSoil=http://www.lonesock.net/files/soil.zip
#Le site de GLM a tendance à être down donc Google Drive
urlGlm="https://drive.google.com/uc?export=download&id=0BzQv_tPVTNPRX1BmdEg2ZFZwdFE"
urlCMake=https://cmake.org/files/v3.8/cmake-3.8.0-rc4.tar.gz

installSuccessful="true"

dir=`pwd`

# Fonction pour confirmer l'install
confirm() {
  # call with a prompt string or use a default
  read -r -p "$1" response
  case "$response" in
    [yY][eE][sS]|[yY]) 
      echo "true"
      ;;
    *)
      echo "false"
      ;;
  esac
}

# Fonctions d'install
installGlew() {
  if [ "$1" = "true" ]
  then 
    isConfirmed="true"
  else
    isConfirmed=`confirm "~/bin/glew-2.0.0 is already there do you wish to re-run install ? [y/N] "`
  fi
  if [ "$isConfirmed" = "true" ]
  then
    echo "Make sure the following are installed: build-essential libXmu-dev libXi-dev libgl-dev git cmake"
    cd glew-2.0.0/build
    cmake ./cmake && make -j4
    if [ $? -eq 0 ]
    then
      echo "GLEW INSTALL SUCCESSFUL"
    else
      echo "GLEW INSTALL FAILED"
      installSuccessful="false"
    fi
    cd ../..
  fi
}

installGlfw() {
  if [ "$1" = "true" ]
  then 
    isConfirmed="true"
  else
    isConfirmed=`confirm "~/bin/glfw-3.2.1 is already there do you wish to re-run install ? [y/N] "`
  fi
  if [ "$isConfirmed" = "true" ]
  then
    echo "Make sure the following are installed: build-essential libXmu-dev libXi-dev libgl-dev git cmake"
    cd glfw-3.2.1
    cmake . && make -j4
    if [ $? -eq 0 ]
    then
      echo "GLFW INSTALL SUCCESSFUL"
    else
      echo "GLFW INSTALL FAILED"
      installSuccessful="false"
    fi
    cd ..
  fi
}

installSoil() {
  if [ "$1" = "true" ]
  then 
    isConfirmed="true"
  else
    isConfirmed=`confirm "~/bin/soil is already there do you wish to re-run install ? [y/N] "`
  fi
  if [ "$isConfirmed" = "true" ]
  then
    cd soil/projects/makefile
    mv makefile makefile2
    cat makefile2 | sed -e 's|/usr/local|~/bin/soil|' | sed '/$(COPIER) $(BIN) $(LOCAL)/d' > Makefile

    mkdir obj
    make -j4 install
    if [ $? -eq 0 ]
    then
      echo "SOIL INSTALL SUCCESSFUL"
    else
      echo "SOIL INSTALL FAILED"
      installSuccessful="false"
    fi
    cd ../../..
  fi
}

installCMake() {
echo "Building latest CMake, this will take a while..."
wget $urlCMake  2> /dev/null && tar -xvzf cmake-3.8.0-rc4.tar.gz > /dev/null && rm cmake-3.8.0-rc4.tar.gz
cd cmake-3.8.0-rc4
./bootstrap > /dev/null && gmake > /dev/null 2>&1
if [ $? -eq 0 ]
then
  echo "Lastest cmake built, adding ~/bin/cmake-3.8.0-rc4 to path..."
  isConfirmed=`confirm "Do you want to you want to add this version of cmake permanently to your PATH ? [y/N] "`
  if [ $"isConfirmed" = "true" ]
  then
    echo "Note: the bashrc file is reset on every reboot at the university."
    echo "export PATH=~/bin/cmake-3.8.0-rc4/bin:$PATH" >> .bashrc
    source ~/.bashrc/
  fi
  export PATH=~/bin/cmake-3.8.0-rc4/bin:$PATH
else
  echo "Lastest cmake build failed, exiting..."
  exit 0
fi
cd ..
}

# Check du répertoire ~/bin
if [ -d $bin ]
then
  isEmpty=`ls -l $bin | sed  -n '2,$p' | wc -l`
  if [ $isEmpty -gt 0 ]
  then
    isConfirmed=`confirm "~/bin not empty, do you wish to continue ? [y/N] "`
    if [ "$isConfirmed" = "true" ]
    then
      echo "Continuing..."
    else
      exit 0
    fi
  fi
else
  echo $bin" doesn't exist, making "$bin"..."
  mkdir $bin
fi

cd $bin

# Check de Glew
if [ -d glew-2.0.0 ]
then
  installGlew false
else
  wget $urlGlew -O glew-2.0.0.zip 2> /dev/null && unzip glew-2.0.0.zip > /dev/null && rm glew-2.0.0.zip
  installGlew true
fi

# Check de Glfw
if [ -d glfw-3.2.1 ]
then
  installGlfw false
else
  wget $urlGlfw 2> /dev/null && unzip glfw-3.2.1.zip > /dev/null && rm glfw-3.2.1.zip
  installGlfw true
fi

# Check de Soil
if [ -d soil ]
then
  installSoil false
else
  wget $urlSoil 2> /dev/null && unzip soil.zip > /dev/null && rm soil.zip && mv Simple\ OpenGL\ Image\ Library soil
  installSoil true
fi

# Check de glm
if [ -d glm ]
then
  echo "~/bin/glm is already there, no need to re-install."
else
  wget $urlGlm -O glm.zip 2> /deV/null && unzip glm.zip > /dev/null && rm glm.zip
  echo "GLM INSTALL SUCCESSFUL"
fi

# Build
if [ "$installSuccessful" = "true" ]
then
  isConfirmed=`confirm "Do you wish to build the project ? [y/N] "`
  if [ "$isConfirmed" = "true" ]
  then
    # Check cmake version
    cMakeVersion=`cmake --version | head -n 1 | cut -d ' ' -f 3`
    cMakeMajor=`echo $cMakeVersion | cut -d '.' -f 1`
    cMakeMinor=`echo $cMakeVersion | cut -d '.' -f 2`
    echo "Need at least cmake version 3.6, you have $cMakeVersion"
    if [ $cMakeMajor -le 3 ]
    then
      if [ $cMakeMajor -eq 3 ]
      then
        if [ $cMakeMinor -lt 6 ]
	then
	  installCMake
	fi
      else
        installCMake
      fi
    fi

    # Building project
    cd $dir
    cmake CMakeLists.txt && make
    if [ $? -eq 0 ]
    then
        echo "Project build successful. Exiting..."
    else
        echo "Can't build the project. Exiting..."
    fi
  else
    echo "Install went fine. Exiting..."
  fi
else
  echo "Install went wrong, can't build the project. Exiting..."
fi

exit 0
