LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame


LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				   ../../Classes/frog.cpp \
				   ../../Classes/froggenerator.cpp \
				   ../../Classes/gamebackgroundlayer.cpp \
				   ../../Classes/gamelayer.cpp \
				   ../../Classes/gameopeninglayer.cpp \
				   ../../Classes/gameoverlayer.cpp \
				   ../../Classes/gamescene.cpp \
				   ../../Classes/gold.cpp \
				   ../../Classes/goldgenerator.cpp \
				   ../../Classes/hublayer.cpp \
				   ../../Classes/object.cpp \
				   ../../Classes/platform.cpp \
				   ../../Classes/platformgenerator.cpp \
				   ../../Classes/player.cpp \
				   ../../Classes/splashscene.cpp \
				   ../../Classes/statistics.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
