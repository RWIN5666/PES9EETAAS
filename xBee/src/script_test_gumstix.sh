#!/bin/sh
# Test Bateau avec les 2 fonctionnalités voulues
gst-launch -v v4l2src always-copy=FALSE ! video/x-raw-yuv,width=576,height=720,framerate=25/1 ! TIVidResize contiguousInputFrame=TRUE ! 'video/x-raw-yuv,width=320,height=240' ! videorate ! 'video/x-raw-yuv,framerate=12/1' !  TIVidenc1 codecName=h264enc engineName=codecServer contiguousInputFrame=FALSE bitRate=100000 rateControlPreset=2 ! queue ! tee name=t t. ! queue ! rtph264pay pt=96 ! udpsink host=$1 port=$2 t. ! queue ! avimux ! filesink location=truc.avi &


#Test enregistrement fichier
gst-launch -v v4l2src always-copy=FALSE ! video/x-raw-yuv,width=576,height=720,framerate=25/1 ! TIVidResize contiguousInputFrame=TRUE ! 'video/x-raw-yuv,width=320,height=240' ! videorate ! 'video/x-raw-yuv,framerate=12/1' !  TIVidenc1 codecName=h264enc engineName=codecServer contiguousInputFrame=FALSE bitRate=100000 rateControlPreset=2 ! avimux ! filesink location=blabla.avi &

# Test Streaming simple
