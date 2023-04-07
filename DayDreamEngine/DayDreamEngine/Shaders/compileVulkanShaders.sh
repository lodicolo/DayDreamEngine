#!/usr/bin/env bash

glslc vertex.vert -o vertex.spv
glslc pixel.frag -o pixel.spv
glslc Texture_vertex.vert -o Texture_vertex.spv
glslc Texture_pixel.frag -o Texture_pixel.spv
