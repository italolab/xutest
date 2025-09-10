#!/bin/bash

VERSION=1.0
SO=linux
ARCH=x64

DEB_CONTROL_PACKAGE_NAME=cbtest
DEB_CONTROL_INSTALLED_SIZE=116
DEB_CONTROL_MAINTAINER="Italo Herbert Siqueira Gabriel (italoherbert@outlook.com)"
DEB_CONTROL_DESCRIPTION="Trata-se de um framework para testes de unidade em C/C++"

APP_FILE_NAME=cbtest
LIB_FILE_NAME=libcbtest.a

BUILD_FOLDER=build
APP_FOLDER=cbtest-$VERSION-$SO-$ARCH

APP_DIR=$BUILD_FOLDER/$APP_FOLDER

APP_LIB_FILE=$APP_DIR/$LIB_FILE_NAME

DEB_APP_DIR=$APP_DIR-deb

DEB_CONTROL_FILE=$DEB_APP_DIR/DEBIAN/control

# LIMPANDO...

if [ -d "$APP_DIR" ]; then
    rm -rf $APP_DIR
    echo "Removido: $APP_DIR"
fi

if [ -d "$DEB_APP_DIR" ]; then
    rm -rf $DEB_APP_DIR
    echo "Removido: $DEB_APP_DIR"
fi

if [ -f "$APP_DIR.tar.gz" ]; then
    rm "$APP_DIR.tar.gz"
    echo "Removido: $APP_DIR.tar.gz"
fi

if [ -f "$APP_DIR.deb" ]; then
    rm "$APP_DIR.deb"
    echo "Removido: $APP_DIR.deb"
fi

mkdir -p $APP_DIR
mkdir -p $DEB_APP_DIR

echo

# COMPILANDO...

./cbuild archivebuild --script=CBuildFile-StaticLib

# COPIANDO HEADERS PARA A PASTA INCLUDE DO SOFTWARE EM BUILD

mkdir $APP_DIR/include
cp -r src/* $APP_DIR/include

# EMPACOTANDO EM .TAR.GZ

cd $BUILD_FOLDER

echo
echo "Empacotando... $APP_DIR.tar.gz"

tar -czf "$APP_FOLDER.tar.gz" $APP_FOLDER
echo "Finalizado." 

cd - &> /dev/null


# Copiando a static library para pasta /usr/lib do .DEB

mkdir -p $DEB_APP_DIR/usr/lib/x86_64-linux-gnu
cp $APP_LIB_FILE $DEB_APP_DIR/usr/lib/x86_64-linux-gnu/$LIB_FILE_NAME

# Copiando os headers para pasta /usr/include do .DEB

mkdir -p $DEB_APP_DIR/usr/include
cp -r $APP_DIR/include/* $DEB_APP_DIR/usr/include


# GERANDO O ARQUIVO CONTROL DO .DEB

mkdir -p $DEB_APP_DIR/DEBIAN

echo "Package: $DEB_CONTROL_PACKAGE_NAME" >> $DEB_CONTROL_FILE
echo "Version: $VERSION" >> $DEB_CONTROL_FILE
echo "Section: games" >> $DEB_CONTROL_FILE
echo "Architecture: amd64" >> $DEB_CONTROL_FILE
echo "Installed-Size: $DEB_CONTROL_INSTALLED_SIZE" >> $DEB_CONTROL_FILE
echo "Maintainer: $DEB_CONTROL_MAINTAINER" >> $DEB_CONTROL_FILE
echo "Description: $DEB_CONTROL_DESCRIPTION" >> $DEB_CONTROL_FILE

# EMPACOTANDO EM .DEB

echo
echo "Empacotando... $APP_DIR.deb"
dpkg-deb -b "$DEB_APP_DIR/" "$APP_DIR.deb"
echo "Finalizado."


# BUILD CONCLUIDO

echo
echo "Build concluido!"