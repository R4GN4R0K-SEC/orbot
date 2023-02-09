#!/bin/sh

rm *aar *jar
if [ ! -d OrbotIPtProxy ]; then
   git clone https://github.com/bitmold/OrbotIPtProxy
fi
cd OrbotIPtProxy
git pull
bash build-orbot.sh
mv OrbotLib.aar ..
mv OrbotLib-sources.jar ..
cd ..