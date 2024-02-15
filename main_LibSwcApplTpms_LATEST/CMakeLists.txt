cmake_minimum_required(VERSION 3.25.3)

project(
   vEcu_vBcIsBpTpms_LibSwcApplTpms_LATEST
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
#  ${PROJECT_SOURCE_DIR}/source/CtApHufTPMSdia
#  ${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr
#  ${PROJECT_SOURCE_DIR}/source/CtApHufTPMSwnh
#  ${PROJECT_SOURCE_DIR}/source/CtApHufTPMSwpa
#  ${PROJECT_SOURCE_DIR}/source/CtCdHufTPMSohds
#  ${PROJECT_SOURCE_DIR}/source/CtCdHufTPMSrfd
   ${PROJECT_SOURCE_DIR}/source/wrappers/main.c
)

target_include_directories(
   ${PROJECT_NAME} PUBLIC

   "${PROJECT_SOURCE_DIR}/source/SwcApplTpmsHmiHandler"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSdia"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/Datamanager"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/DevMsg"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/E2ELib"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/FDmanager"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/Interfaces"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSmgr/Statemanager"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSwnh/WarnHler"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSwpa/Walloc"
   "${PROJECT_SOURCE_DIR}/source/CtApHufTPMSwpa/CtCdHufTPMSohds"
   "${PROJECT_SOURCE_DIR}/source/CtCdHufTPMSrfd"
   "${PROJECT_SOURCE_DIR}/source/wrappers"
)
