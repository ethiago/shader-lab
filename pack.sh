#!/bin/bash

APPPATH="output"
DEBPATH="$APPPATH/DEBIAN"
BINPATH=usr/$BINNAME/$BINNAME-$VER

mkdir $DEBPATH

cat > "$DEBPATH/control" << EOM
Source: ShaderLabs
Package: ShaderLabs
Version: $VER
Maintainer: Thiago Gomes <thiagoegomes@gmail.com>
Section: graphics
Priority: optional
Architecture: all
Depends: libglu1-mesa
Description: ShaderLabs is a IDE for GLSL experimentation
 ShaderLabs provides a abstraction over a OpenGL aplication so you can 
 focus on learn or propotype your OpenGL vertex, fragment, geometry 
 or tessellation shaders.
EOM

cat > "$DEBPATH/postinst" << EOM
ln -sf /$BINPATH/bin/$BINNAME /usr/bin/$BINNAME
EOM

chmod +x $DEBPATH/postinst

mkdir -p $APPPATH/$BINPATH

mv $APPPATH/bin $APPPATH/$BINPATH/

dpkg-deb --build $APPPATH
EXC=$?

mv ./${APPPATH}.deb ./${BINNAME}_${VER}.deb

exit $EXC
