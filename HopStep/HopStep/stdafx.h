// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.

#include <Windows.h>
#include <memory.h>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <iosfwd>
#include <chrono>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stack>
#include <deque>
#include <thread>
#include <cstddef>
#include <algorithm>
#include <sstream>
#include <type_traits>
#include <cassert>


// DirectX Headers
#include <D2D1.h>
#pragma comment(lib, "D2D1.lib")

#include "DirectXDefine.h"

// Extern Headers
#include "../Extern/Jsoncpp/include/json/json.h"
#pragma comment(lib, "json_vc71_libmtd.lib")

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Result.h"
#include "HSDebug.h"
#include "CheckResult.h"
#include "InputLayer.h"
#include "IDGenerator.h"
#include "HSColor.h"
#include "HSVector.h"
#include "FrameInfo.h"
#include "StringHelper.h"
#include "JsonSerialize.h"
#include "HSConsoleLogger.h"
#include "RenderQueue.h"
#include "HSHandle.h"