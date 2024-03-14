cmake_minimum_required(VERSION 3.25.3)

project(
   vEcu_iSolarV12.00.00_MinGwV06.03.00_NxpS32K146_vBcIsBpTpms_LATEST
   VERSION 0.1
)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

add_definitions(
   -g
   -std=c2x
   -Wall
   -Werror
   -Wextra
   -pedantic
   -Wuninitialized
   -D CfgProject_dSwitchReSim
)

add_executable(
   ${PROJECT_NAME}

   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsHmiHandler/SwcApplTpmsHmiHandler.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler/ctrl.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler/DAG_TVWarn.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler/TSSMsg.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler/USWarn.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler/uswarn_If.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler/WTDHW.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler/WTEcE.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler/WTPmin.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler/WTSFactor.c
   ${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWpa/FPA.c

#  ${PROJECT_SOURCE_DIR}/source/CtApHufTPMSdia
#  ${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr
#  ${PROJECT_SOURCE_DIR}/source/CtApHufTPMSwnh
#  ${PROJECT_SOURCE_DIR}/source/CtCdHufTPMSrfd
   ${PROJECT_SOURCE_DIR}/source/wrappers/main.c
)

target_include_directories(
   ${PROJECT_NAME} PUBLIC

   "${PROJECT_SOURCE_DIR}/source/SwcApplTpmsHmiHandler"
   "${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWarnHandler"
   "${PROJECT_SOURCE_DIR}/source/SwcApplTpmsWpa"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSdia"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/Datamanager"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/DevMsg"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/E2ELib"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/FDmanager"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/Interfaces"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/Statemanager"
   "${PROJECT_SOURCE_DIR}/source/CtCdHufTPMSrfd"
   "${PROJECT_SOURCE_DIR}/source/stubs"
)
