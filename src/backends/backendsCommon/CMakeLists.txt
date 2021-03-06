#
# Copyright © 2017 Arm Ltd. All rights reserved.
# SPDX-License-Identifier: MIT
#

list(APPEND armnnBackendsCommon_sources
    BackendRegistry.cpp
    BackendRegistry.hpp
    CpuTensorHandle.cpp
    CpuTensorHandleFwd.hpp
    CpuTensorHandle.hpp
    IBackendInternal.hpp
    IBackendContext.hpp
    LayerSupportBase.cpp
    LayerSupportBase.hpp
    IMemoryManager.hpp
    ITensorHandle.hpp
    MakeWorkloadHelper.hpp
    MemCopyWorkload.cpp
    MemCopyWorkload.hpp
    OutputHandler.cpp
    OutputHandler.hpp
    WorkloadDataCollector.hpp
    WorkloadData.cpp
    WorkloadDataFwd.hpp
    WorkloadData.hpp
    WorkloadFactory.cpp
    WorkloadFactory.hpp
    Workload.hpp
    WorkloadInfo.hpp
    WorkloadUtils.cpp
    WorkloadUtils.hpp
)

if(BUILD_UNIT_TESTS)
    add_subdirectory(test)
endif()

add_library(armnnBackendsCommon OBJECT ${armnnBackendsCommon_sources})
target_include_directories(armnnBackendsCommon PRIVATE ${PROJECT_SOURCE_DIR}/src/armnn)
target_include_directories(armnnBackendsCommon PRIVATE ${PROJECT_SOURCE_DIR}/src/armnnUtils)
target_include_directories(armnnBackendsCommon PRIVATE ${PROJECT_SOURCE_DIR}/src/backends)
