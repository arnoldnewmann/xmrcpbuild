#ifndef __VERSION_H__
#define __VERSION_H__

#define APP_ID        "xmrig"
#define APP_NAME      "XMRig"
#define APP_DESC      "XMRig CPU miner"
#define APP_VERSION   "2.3.1"
#define APP_DOMAIN    "xmrig.com"
#define APP_SITE      "www.xmrig.com"
#define APP_COPYRIGHT "Copyright (C) 2016-2017 xmrig.com"

#define APP_VER_MAJOR  2
#define APP_VER_MINOR  3
#define APP_VER_BUILD  1
#define APP_VER_REV    0

#ifdef _MSC_VER
#   if _MSC_VER == 1910
#       define MSVC_VERSION 2017
#   elif _MSC_VER == 1900
#       define MSVC_VERSION 2015
#   elif _MSC_VER == 1800
#       define MSVC_VERSION 2013
#   elif _MSC_VER == 1700
#       define MSVC_VERSION 2012
#   elif _MSC_VER == 1600
#       define MSVC_VERSION 2010
#   else
#       define MSVC_VERSION 0
#   endif
#endif

#endif /* __VERSION_H__ */
