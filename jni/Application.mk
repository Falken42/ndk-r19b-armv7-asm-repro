APP_STL := c++_shared
APP_CFLAGS := 
APP_CPPFLAGS := -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -mthumb -fno-integrated-as -Os -fno-stack-protector -funsigned-char -fno-common -std=c++1y -stdlib=libc++ -fno-exceptions -fno-rtti -fpic -ffunction-sections -fdata-sections -funwind-tables -fvisibility=hidden -Wno-invalid-command-line-argument -Wno-unused-command-line-argument -no-canonical-prefixes -Wa,--noexecstack -Wformat -Werror=format-security
APP_PLATFORM := android-24
APP_ABI := armeabi-v7a
