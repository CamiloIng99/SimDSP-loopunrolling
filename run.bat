call ndk-build clean
call ndk-build
call xcopy /Y obj\local\armeabi-v7a\simdsp simdspf\simdsp
call adb push simdspf/. /data/local/tmp/simdspf


