/*
 * PD_Controller_design_dt.h
 *
 * Code generation for model "PD_Controller_design.mdl".
 *
 * Model version              : 1.460
 * Simulink Coder version : 8.1 (R2011b) 08-Jul-2011
 * C source code generated on : Fri Oct 20 16:57:32 2017
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_card),
  sizeof(t_boolean),
  sizeof(t_task)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_card",
  "t_boolean",
  "t_task"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&PD_Controller_design_B.HILReadTimebase[0]), 0, 0, 23 }
  ,

  { (char_T *)(&PD_Controller_design_DWork.HILInitialize_AIMinimums[0]), 0, 0,
    24 },

  { (char_T *)(&PD_Controller_design_DWork.HILInitialize_Card), 14, 0, 1 },

  { (char_T *)(&PD_Controller_design_DWork.HILReadTimebase_Task), 16, 0, 1 },

  { (char_T *)(&PD_Controller_design_DWork.Derivative_RWORK.TimeStampA), 0, 0, 1
  },

  { (char_T *)(&PD_Controller_design_DWork.Scope_PWORK.LoggedData), 11, 0, 4 },

  { (char_T *)(&PD_Controller_design_DWork.HILInitialize_DOStates[0]), 6, 0, 15
  },

  { (char_T *)(&PD_Controller_design_DWork.HILInitialize_DOBits[0]), 8, 0, 4 },

  { (char_T *)(&PD_Controller_design_DWork.HILWriteDigital_Buffer[0]), 15, 0, 4
  }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  9U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&PD_Controller_design_P.gainfor2DPantoamplifier_Gain), 0, 0, 37 },

  { (char_T *)(&PD_Controller_design_P.HILInitialize_CKChannels[0]), 6, 0, 8 },

  { (char_T *)(&PD_Controller_design_P.HILInitialize_AIChannels[0]), 7, 0, 27 },

  { (char_T *)(&PD_Controller_design_P.HILInitialize_Active), 8, 0, 38 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  4U,
  rtPTransitions
};

/* [EOF] PD_Controller_design_dt.h */
