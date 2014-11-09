# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)/..

#******************************************#
#
#                 Common
#
#******************************************#

include $(CLEAR_VARS)

#LOCAL_CPP_EXTENSION := cpp

LOCAL_MODULE    := Common

#LOCAL_ARM_MODE := arm

#just for shared library
#TARGET_PRELINK_MODULES := false

MY_SRC_FILES := fileutil.cpp \
                inifile.cpp \
                iniutil.cpp \
                logger.cpp \
                optutil.cpp \
                pathutil.cpp \
                strutil.cpp \
                sysutil.cpp \
                timeutil.cpp

MY_INCLUDE :=

MY_CFLAGS := exceptions rtti


LOCAL_SRC_FILES := $(MY_SRC_FILES)

#LOCAL_STATIC_LIBRARIES :=

#LOCAL_SHARED_LIBRARIES := 

LOCAL_LDLIBS :=

LOCAL_CPP_FEATURES += $(MY_INCLUDE) $(MY_CFLAGS)

LOCAL_CFLAGS += -fvisibility=hidden 

include $(BUILD_STATIC_LIBRARY)


