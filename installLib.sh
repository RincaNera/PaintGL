bin=~/bin

urlGlew="https://downloads.sourceforge.net/project/glew/glew/2.0.0/glew-2.0.0.zip?ts=1491410177"
urlGlfw=https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
urlSoil=http://www.lonesock.net/files/soil.zip
#Le site de GLM a tendance à être down donc Google Drive
urlGlm="https://drive.google.com/uc?export=download&id=0BzQv_tPVTNPRX1BmdEg2ZFZwdFE"

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
      installsuccessful="false"
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
      instalsuccessful="false"
    fi
    cd ..
  fi
}

installSoil() {
  if [ "$1" = "true" ]
  then 
    isConfirmed="true"
  else
    isConfirmed=`confirm "~/bin/Simple OpenGL Image Library  is already there do you wish to re-run install ? [y/N] "`
  fi
  if [ "$isConfirmed" = "true" ]
  then
    cd Simple\ OpenGL\ Image\ Library/projects/makefile
    make -j4
    if [ $? -eq 0 ]
    then
      echo "SOIL INSTALL SUCCESSFUL"
    else
      echo "SOIL INSTALL FAILED"
      installsuccessful="false"
    fi
    cd ../../..
  fi
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
  wget $urlGlew -O glew-2.0.0.zip && unzip glew2.0.0.zip && rm glew.2.0.0.zip
  installGlew true
fi

# Check de Glfw
if [ -d glfw-3.2.1 ]
then
  installGlfw false
else
  wget $urlGlfw && unzip glfw-3.2.1.zip && rm glfw-3.2.1.zip
  installGlfw true
fi

# Check de Soil
if [ -d Simple\ OpenGL\ Image\ Library ]
then
  installSoil false
else
  wget $urlSoil && unzip soil.zip && rm soil.zip
  installSoil true
fi

# Check de glm
if [ -d glm ]
then
  echo "~/bin/glm is already there, no need to re-install."
else
  wget $urlGlm -O glm.zip && unzip glm.zip && rm glm.zip
  echo "GLM INSTALL SUCCESSFUL"
fi

# Build
if [ "$installSuccessful" = "true" ]
then
  isConfirmed=`confirm "Do you wish to build the project ? [y/N] "`
  if [ "$isConfirmed" = "true" ]
  then
    cd $dir
    make CMakeLists.txt && make
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
