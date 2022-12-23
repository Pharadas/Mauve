for file in ./uncompiled_shaders/*; do
  glslc ./uncompiled_shaders/"${file##*/}" -o ./shaders/"${file##*/}".spv;
  echo "${file##*/}" compiled succesully;
done
