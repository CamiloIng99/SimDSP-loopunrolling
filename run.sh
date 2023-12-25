ndk-build clean
ndk-build
cp obj/local/armeabi-v7a/simdsp simdspf

adb push simdspf/. /data/local/tmp/simdspf
