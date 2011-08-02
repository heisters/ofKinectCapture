#!/usr/bin/env bash

ffmpeg -i bin/data/out/visible-%06d.bmp -r 30 -vcodec libx264 -b 8000k bin/data/visible.mov
ffmpeg -i bin/data/out/depth-%06d.bmp -r 30 -vcodec libx264 -b 8000k bin/data/depth.mov
