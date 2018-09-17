/*
 * robot_demo.c
 *
 * Code generation for model "robot_demo.mdl".
 *
 * Model version              : 1.420
 * Simulink Coder version : 8.1 (R2011b) 08-Jul-2011
 * C source code generated on : Tue Sep 25 14:29:30 2012
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "robot_demo.h"
#include "robot_demo_private.h"
#include "robot_demo_dt.h"

/* Block signals (auto storage) */
BlockIO_robot_demo robot_demo_B;

/* Block states (auto storage) */
D_Work_robot_demo robot_demo_DWork;

/* Real-time model */
RT_MODEL_robot_demo robot_demo_M_;
RT_MODEL_robot_demo *const robot_demo_M = &robot_demo_M_;

/* Model output function */
void robot_demo_output(int_T tid)
{
  /* S-Function (hil_read_timebase_block): '<S2>/HIL Read Timebase' */

  /* S-Function Block: robot_demo/Encoders/HIL Read Timebase (hil_read_timebase_block) */
  {
    t_error result;
    result = hil_task_read(robot_demo_DWork.HILReadTimebase_Task, 1,
      NULL,
      &robot_demo_DWork.HILReadTimebase_EncoderBuffer[0],
      NULL,
      NULL
      );
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(robot_demo_M, _rt_error_message);
    } else {
      robot_demo_B.HILReadTimebase[0] =
        robot_demo_DWork.HILReadTimebase_EncoderBuffer[0];
      robot_demo_B.HILReadTimebase[1] =
        robot_demo_DWork.HILReadTimebase_EncoderBuffer[1];
      robot_demo_B.HILReadTimebase[2] =
        robot_demo_DWork.HILReadTimebase_EncoderBuffer[2];
    }
  }

  /* Sum: '<S1>/Add' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<S1>/Constant'
   */
  robot_demo_B.Add[0] = robot_demo_P.Constant_Value[0] +
    robot_demo_P.Constant_Value_m;
  robot_demo_B.Add[1] = robot_demo_P.Constant_Value[1] +
    robot_demo_P.Constant_Value_m;

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant1'
   */
  if (robot_demo_P.Constant1_Value > robot_demo_P.Switch_Threshold) {
    /* Gain: '<S1>/gain for 2DPanto new amplifier' */
    robot_demo_B.gainfor2DPantonewamplifier[0] =
      robot_demo_P.gainfor2DPantonewamplifier_Gain * robot_demo_B.Add[0];
    robot_demo_B.gainfor2DPantonewamplifier[1] =
      robot_demo_P.gainfor2DPantonewamplifier_Gain * robot_demo_B.Add[1];
    robot_demo_B.Switch[0] = robot_demo_B.gainfor2DPantonewamplifier[0];
    robot_demo_B.Switch[1] = robot_demo_B.gainfor2DPantonewamplifier[1];
  } else {
    /* Gain: '<S1>/gain for 2DPanto amplifier' */
    robot_demo_B.gainfor2DPantoamplifier[0] =
      robot_demo_P.gainfor2DPantoamplifier_Gain * robot_demo_B.Add[0];
    robot_demo_B.gainfor2DPantoamplifier[1] =
      robot_demo_P.gainfor2DPantoamplifier_Gain * robot_demo_B.Add[1];
    robot_demo_B.Switch[0] = robot_demo_B.gainfor2DPantoamplifier[0];
    robot_demo_B.Switch[1] = robot_demo_B.gainfor2DPantoamplifier[1];
  }

  /* End of Switch: '<S1>/Switch' */

  /* Gain: '<S1>/K1' */
  robot_demo_B.K1[0] = robot_demo_P.K1_Gain[0] * robot_demo_B.Switch[0];
  robot_demo_B.K1[1] = robot_demo_P.K1_Gain[1] * robot_demo_B.Switch[1];

  /* S-Function (hil_write_analog_block): '<S1>/HIL Write Analog' */

  /* S-Function Block: robot_demo/2Dpanto motor/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(robot_demo_DWork.HILInitialize_Card,
      robot_demo_P.HILWriteAnalog_Channels, 2, robot_demo_B.K1);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(robot_demo_M, _rt_error_message);
    }
  }

  /* S-Function (hil_write_digital_block): '<S1>/HIL Write Digital' */

  /* S-Function Block: robot_demo/2Dpanto motor/HIL Write Digital (hil_write_digital_block) */
  {
    t_error result;
    robot_demo_DWork.HILWriteDigital_Buffer[0] = (robot_demo_P.Constant_Value_e
      [0] != 0);
    robot_demo_DWork.HILWriteDigital_Buffer[1] = (robot_demo_P.Constant_Value_e
      [1] != 0);
    robot_demo_DWork.HILWriteDigital_Buffer[2] = (robot_demo_P.Constant_Value_e
      [2] != 0);
    robot_demo_DWork.HILWriteDigital_Buffer[3] = (robot_demo_P.Constant_Value_e
      [3] != 0);
    result = hil_write_digital(robot_demo_DWork.HILInitialize_Card,
      robot_demo_P.HILWriteDigital_Channels, 4,
      &robot_demo_DWork.HILWriteDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(robot_demo_M, _rt_error_message);
    }
  }

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Constant1'
   */
  if (robot_demo_P.Constant1_Value_j > robot_demo_P.Switch_Threshold_d) {
    /* Gain: '<S2>/gain t1 for 2dPanto new' */
    robot_demo_B.gaint1for2dPantonew = robot_demo_P.gaint1for2dPantonew_Gain *
      robot_demo_B.HILReadTimebase[0];
    robot_demo_B.Switch_m = robot_demo_B.gaint1for2dPantonew;
  } else {
    /* Gain: '<S2>/gain t1 for 2dPanto' */
    robot_demo_B.gaint1for2dPanto = robot_demo_P.gaint1for2dPanto_Gain *
      robot_demo_B.HILReadTimebase[0];
    robot_demo_B.Switch_m = robot_demo_B.gaint1for2dPanto;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Sum: '<S2>/Sum' incorporates:
   *  Constant: '<S2>/Constant2'
   */
  robot_demo_B.Sum = robot_demo_B.Switch_m + robot_demo_P.Constant2_Value;

  /* Gain: '<S2>/gain t1 for 2dPanto new1' */
  robot_demo_B.gaint1for2dPantonew1 = robot_demo_P.gaint1for2dPantonew1_Gain *
    robot_demo_B.HILReadTimebase[2];

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S2>/Constant3'
   */
  robot_demo_B.Sum1 = robot_demo_P.Constant3_Value +
    robot_demo_B.gaint1for2dPantonew1;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void robot_demo_update(int_T tid)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++robot_demo_M->Timing.clockTick0)) {
    ++robot_demo_M->Timing.clockTickH0;
  }

  robot_demo_M->Timing.t[0] = robot_demo_M->Timing.clockTick0 *
    robot_demo_M->Timing.stepSize0 + robot_demo_M->Timing.clockTickH0 *
    robot_demo_M->Timing.stepSize0 * 4294967296.0;

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model initialize function */
void robot_demo_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)robot_demo_M, 0,
                sizeof(RT_MODEL_robot_demo));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = robot_demo_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    robot_demo_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    robot_demo_M->Timing.sampleTimes = (&robot_demo_M->Timing.sampleTimesArray[0]);
    robot_demo_M->Timing.offsetTimes = (&robot_demo_M->Timing.offsetTimesArray[0]);

    /* task periods */
    robot_demo_M->Timing.sampleTimes[0] = (0.001);

    /* task offsets */
    robot_demo_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(robot_demo_M, &robot_demo_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = robot_demo_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    robot_demo_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(robot_demo_M, -1);
  robot_demo_M->Timing.stepSize0 = 0.001;

  /* external mode info */
  robot_demo_M->Sizes.checksums[0] = (2505567716U);
  robot_demo_M->Sizes.checksums[1] = (503085668U);
  robot_demo_M->Sizes.checksums[2] = (2292585632U);
  robot_demo_M->Sizes.checksums[3] = (1534021269U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    robot_demo_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(robot_demo_M->extModeInfo,
      &robot_demo_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(robot_demo_M->extModeInfo, robot_demo_M->Sizes.checksums);
    rteiSetTPtr(robot_demo_M->extModeInfo, rtmGetTPtr(robot_demo_M));
  }

  robot_demo_M->solverInfoPtr = (&robot_demo_M->solverInfo);
  robot_demo_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&robot_demo_M->solverInfo, 0.001);
  rtsiSetSolverMode(&robot_demo_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  robot_demo_M->ModelData.blockIO = ((void *) &robot_demo_B);

  {
    robot_demo_B.HILReadTimebase[0] = 0.0;
    robot_demo_B.HILReadTimebase[1] = 0.0;
    robot_demo_B.HILReadTimebase[2] = 0.0;
    robot_demo_B.Add[0] = 0.0;
    robot_demo_B.Add[1] = 0.0;
    robot_demo_B.Switch[0] = 0.0;
    robot_demo_B.Switch[1] = 0.0;
    robot_demo_B.K1[0] = 0.0;
    robot_demo_B.K1[1] = 0.0;
    robot_demo_B.Switch_m = 0.0;
    robot_demo_B.Sum = 0.0;
    robot_demo_B.gaint1for2dPantonew1 = 0.0;
    robot_demo_B.Sum1 = 0.0;
    robot_demo_B.gaint1for2dPantonew = 0.0;
    robot_demo_B.gaint1for2dPanto = 0.0;
    robot_demo_B.gainfor2DPantonewamplifier[0] = 0.0;
    robot_demo_B.gainfor2DPantonewamplifier[1] = 0.0;
    robot_demo_B.gainfor2DPantoamplifier[0] = 0.0;
    robot_demo_B.gainfor2DPantoamplifier[1] = 0.0;
  }

  /* parameters */
  robot_demo_M->ModelData.defaultParam = ((real_T *)&robot_demo_P);

  /* states (dwork) */
  robot_demo_M->Work.dwork = ((void *) &robot_demo_DWork);
  (void) memset((void *)&robot_demo_DWork, 0,
                sizeof(D_Work_robot_demo));
  robot_demo_DWork.HILInitialize_AIMinimums[0] = 0.0;
  robot_demo_DWork.HILInitialize_AIMinimums[1] = 0.0;
  robot_demo_DWork.HILInitialize_AIMinimums[2] = 0.0;
  robot_demo_DWork.HILInitialize_AIMinimums[3] = 0.0;
  robot_demo_DWork.HILInitialize_AIMaximums[0] = 0.0;
  robot_demo_DWork.HILInitialize_AIMaximums[1] = 0.0;
  robot_demo_DWork.HILInitialize_AIMaximums[2] = 0.0;
  robot_demo_DWork.HILInitialize_AIMaximums[3] = 0.0;
  robot_demo_DWork.HILInitialize_AOMinimums[0] = 0.0;
  robot_demo_DWork.HILInitialize_AOMinimums[1] = 0.0;
  robot_demo_DWork.HILInitialize_AOMinimums[2] = 0.0;
  robot_demo_DWork.HILInitialize_AOMinimums[3] = 0.0;
  robot_demo_DWork.HILInitialize_AOMaximums[0] = 0.0;
  robot_demo_DWork.HILInitialize_AOMaximums[1] = 0.0;
  robot_demo_DWork.HILInitialize_AOMaximums[2] = 0.0;
  robot_demo_DWork.HILInitialize_AOMaximums[3] = 0.0;
  robot_demo_DWork.HILInitialize_AOVoltages[0] = 0.0;
  robot_demo_DWork.HILInitialize_AOVoltages[1] = 0.0;
  robot_demo_DWork.HILInitialize_AOVoltages[2] = 0.0;
  robot_demo_DWork.HILInitialize_AOVoltages[3] = 0.0;
  robot_demo_DWork.HILInitialize_FilterFrequency[0] = 0.0;
  robot_demo_DWork.HILInitialize_FilterFrequency[1] = 0.0;
  robot_demo_DWork.HILInitialize_FilterFrequency[2] = 0.0;
  robot_demo_DWork.HILInitialize_FilterFrequency[3] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    robot_demo_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }
}

/* Model terminate function */
void robot_demo_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: robot_demo/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(robot_demo_DWork.HILInitialize_Card);
    hil_monitor_stop_all(robot_demo_DWork.HILInitialize_Card);
    is_switching = false;
    if ((robot_demo_P.HILInitialize_AOTerminate && !is_switching) ||
        (robot_demo_P.HILInitialize_AOExit && is_switching)) {
      robot_demo_DWork.HILInitialize_AOVoltages[0] =
        robot_demo_P.HILInitialize_AOFinal;
      robot_demo_DWork.HILInitialize_AOVoltages[1] =
        robot_demo_P.HILInitialize_AOFinal;
      robot_demo_DWork.HILInitialize_AOVoltages[2] =
        robot_demo_P.HILInitialize_AOFinal;
      robot_demo_DWork.HILInitialize_AOVoltages[3] =
        robot_demo_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 4U;
    }

    if ((robot_demo_P.HILInitialize_DOTerminate && !is_switching) ||
        (robot_demo_P.HILInitialize_DOExit && is_switching)) {
      robot_demo_DWork.HILInitialize_DOBits[0] =
        robot_demo_P.HILInitialize_DOFinal;
      robot_demo_DWork.HILInitialize_DOBits[1] =
        robot_demo_P.HILInitialize_DOFinal;
      robot_demo_DWork.HILInitialize_DOBits[2] =
        robot_demo_P.HILInitialize_DOFinal;
      robot_demo_DWork.HILInitialize_DOBits[3] =
        robot_demo_P.HILInitialize_DOFinal;
      num_final_digital_outputs = 4U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(robot_demo_DWork.HILInitialize_Card
                         , robot_demo_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , robot_demo_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &robot_demo_DWork.HILInitialize_AOVoltages[0]
                         , NULL
                         , &robot_demo_DWork.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(robot_demo_DWork.HILInitialize_Card,
            robot_demo_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &robot_demo_DWork.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital(robot_demo_DWork.HILInitialize_Card,
            robot_demo_P.HILInitialize_DOChannels, num_final_digital_outputs,
            &robot_demo_DWork.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(robot_demo_DWork.HILInitialize_Card);
    hil_monitor_delete_all(robot_demo_DWork.HILInitialize_Card);
    hil_close(robot_demo_DWork.HILInitialize_Card);
    robot_demo_DWork.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  robot_demo_output(tid);
}

void MdlUpdate(int_T tid)
{
  robot_demo_update(tid);
}

void MdlInitializeSizes(void)
{
  robot_demo_M->Sizes.numContStates = (0);/* Number of continuous states */
  robot_demo_M->Sizes.numY = (0);      /* Number of model outputs */
  robot_demo_M->Sizes.numU = (0);      /* Number of model inputs */
  robot_demo_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  robot_demo_M->Sizes.numSampTimes = (1);/* Number of sample times */
  robot_demo_M->Sizes.numBlocks = (29);/* Number of blocks */
  robot_demo_M->Sizes.numBlockIO = (12);/* Number of block outputs */
  robot_demo_M->Sizes.numBlockPrms = (108);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: robot_demo/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q4", "0", &robot_demo_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(robot_demo_M, _rt_error_message);
      return;
    }

    is_switching = false;
    if ((robot_demo_P.HILInitialize_CKPStart && !is_switching) ||
        (robot_demo_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(robot_demo_DWork.HILInitialize_Card, (t_clock *)
        robot_demo_P.HILInitialize_CKChannels, 2U, (t_clock_mode *)
        robot_demo_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(robot_demo_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(robot_demo_M, _rt_error_message);
      return;
    }

    if ((robot_demo_P.HILInitialize_AIPStart && !is_switching) ||
        (robot_demo_P.HILInitialize_AIPEnter && is_switching)) {
      robot_demo_DWork.HILInitialize_AIMinimums[0] =
        robot_demo_P.HILInitialize_AILow;
      robot_demo_DWork.HILInitialize_AIMinimums[1] =
        robot_demo_P.HILInitialize_AILow;
      robot_demo_DWork.HILInitialize_AIMinimums[2] =
        robot_demo_P.HILInitialize_AILow;
      robot_demo_DWork.HILInitialize_AIMinimums[3] =
        robot_demo_P.HILInitialize_AILow;
      robot_demo_DWork.HILInitialize_AIMaximums[0] =
        robot_demo_P.HILInitialize_AIHigh;
      robot_demo_DWork.HILInitialize_AIMaximums[1] =
        robot_demo_P.HILInitialize_AIHigh;
      robot_demo_DWork.HILInitialize_AIMaximums[2] =
        robot_demo_P.HILInitialize_AIHigh;
      robot_demo_DWork.HILInitialize_AIMaximums[3] =
        robot_demo_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(robot_demo_DWork.HILInitialize_Card,
        robot_demo_P.HILInitialize_AIChannels, 4U,
        &robot_demo_DWork.HILInitialize_AIMinimums[0],
        &robot_demo_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }
    }

    if ((robot_demo_P.HILInitialize_AOPStart && !is_switching) ||
        (robot_demo_P.HILInitialize_AOPEnter && is_switching)) {
      robot_demo_DWork.HILInitialize_AOMinimums[0] =
        robot_demo_P.HILInitialize_AOLow;
      robot_demo_DWork.HILInitialize_AOMinimums[1] =
        robot_demo_P.HILInitialize_AOLow;
      robot_demo_DWork.HILInitialize_AOMinimums[2] =
        robot_demo_P.HILInitialize_AOLow;
      robot_demo_DWork.HILInitialize_AOMinimums[3] =
        robot_demo_P.HILInitialize_AOLow;
      robot_demo_DWork.HILInitialize_AOMaximums[0] =
        robot_demo_P.HILInitialize_AOHigh;
      robot_demo_DWork.HILInitialize_AOMaximums[1] =
        robot_demo_P.HILInitialize_AOHigh;
      robot_demo_DWork.HILInitialize_AOMaximums[2] =
        robot_demo_P.HILInitialize_AOHigh;
      robot_demo_DWork.HILInitialize_AOMaximums[3] =
        robot_demo_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(robot_demo_DWork.HILInitialize_Card,
        robot_demo_P.HILInitialize_AOChannels, 4U,
        &robot_demo_DWork.HILInitialize_AOMinimums[0],
        &robot_demo_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }
    }

    if ((robot_demo_P.HILInitialize_AOStart && !is_switching) ||
        (robot_demo_P.HILInitialize_AOEnter && is_switching)) {
      robot_demo_DWork.HILInitialize_AOVoltages[0] =
        robot_demo_P.HILInitialize_AOInitial;
      robot_demo_DWork.HILInitialize_AOVoltages[1] =
        robot_demo_P.HILInitialize_AOInitial;
      robot_demo_DWork.HILInitialize_AOVoltages[2] =
        robot_demo_P.HILInitialize_AOInitial;
      robot_demo_DWork.HILInitialize_AOVoltages[3] =
        robot_demo_P.HILInitialize_AOInitial;
      result = hil_write_analog(robot_demo_DWork.HILInitialize_Card,
        robot_demo_P.HILInitialize_AOChannels, 4U,
        &robot_demo_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }
    }

    if (robot_demo_P.HILInitialize_AOReset) {
      robot_demo_DWork.HILInitialize_AOVoltages[0] =
        robot_demo_P.HILInitialize_AOWatchdog;
      robot_demo_DWork.HILInitialize_AOVoltages[1] =
        robot_demo_P.HILInitialize_AOWatchdog;
      robot_demo_DWork.HILInitialize_AOVoltages[2] =
        robot_demo_P.HILInitialize_AOWatchdog;
      robot_demo_DWork.HILInitialize_AOVoltages[3] =
        robot_demo_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (robot_demo_DWork.HILInitialize_Card,
         robot_demo_P.HILInitialize_AOChannels, 4U,
         &robot_demo_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(robot_demo_DWork.HILInitialize_Card,
      NULL, 0U, robot_demo_P.HILInitialize_DOChannels, 4U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(robot_demo_M, _rt_error_message);
      return;
    }

    if ((robot_demo_P.HILInitialize_DOStart && !is_switching) ||
        (robot_demo_P.HILInitialize_DOEnter && is_switching)) {
      robot_demo_DWork.HILInitialize_DOBits[0] =
        robot_demo_P.HILInitialize_DOInitial;
      robot_demo_DWork.HILInitialize_DOBits[1] =
        robot_demo_P.HILInitialize_DOInitial;
      robot_demo_DWork.HILInitialize_DOBits[2] =
        robot_demo_P.HILInitialize_DOInitial;
      robot_demo_DWork.HILInitialize_DOBits[3] =
        robot_demo_P.HILInitialize_DOInitial;
      result = hil_write_digital(robot_demo_DWork.HILInitialize_Card,
        robot_demo_P.HILInitialize_DOChannels, 4U, (t_boolean *)
        &robot_demo_DWork.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }
    }

    if (robot_demo_P.HILInitialize_DOReset) {
      robot_demo_DWork.HILInitialize_DOStates[0] =
        robot_demo_P.HILInitialize_DOWatchdog;
      robot_demo_DWork.HILInitialize_DOStates[1] =
        robot_demo_P.HILInitialize_DOWatchdog;
      robot_demo_DWork.HILInitialize_DOStates[2] =
        robot_demo_P.HILInitialize_DOWatchdog;
      robot_demo_DWork.HILInitialize_DOStates[3] =
        robot_demo_P.HILInitialize_DOWatchdog;
      result = hil_watchdog_set_digital_expiration_state
        (robot_demo_DWork.HILInitialize_Card,
         robot_demo_P.HILInitialize_DOChannels, 4U, (const t_digital_state *)
         &robot_demo_DWork.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }
    }

    if ((robot_demo_P.HILInitialize_EIPStart && !is_switching) ||
        (robot_demo_P.HILInitialize_EIPEnter && is_switching)) {
      robot_demo_DWork.HILInitialize_QuadratureModes[0] =
        robot_demo_P.HILInitialize_EIQuadrature;
      robot_demo_DWork.HILInitialize_QuadratureModes[1] =
        robot_demo_P.HILInitialize_EIQuadrature;
      robot_demo_DWork.HILInitialize_QuadratureModes[2] =
        robot_demo_P.HILInitialize_EIQuadrature;
      robot_demo_DWork.HILInitialize_QuadratureModes[3] =
        robot_demo_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (robot_demo_DWork.HILInitialize_Card,
         robot_demo_P.HILInitialize_EIChannels, 4U, (t_encoder_quadrature_mode *)
         &robot_demo_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }

      robot_demo_DWork.HILInitialize_FilterFrequency[0] =
        robot_demo_P.HILInitialize_EIFrequency;
      robot_demo_DWork.HILInitialize_FilterFrequency[1] =
        robot_demo_P.HILInitialize_EIFrequency;
      robot_demo_DWork.HILInitialize_FilterFrequency[2] =
        robot_demo_P.HILInitialize_EIFrequency;
      robot_demo_DWork.HILInitialize_FilterFrequency[3] =
        robot_demo_P.HILInitialize_EIFrequency;
      result = hil_set_encoder_filter_frequency
        (robot_demo_DWork.HILInitialize_Card,
         robot_demo_P.HILInitialize_EIChannels, 4U,
         &robot_demo_DWork.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }
    }

    if ((robot_demo_P.HILInitialize_EIStart && !is_switching) ||
        (robot_demo_P.HILInitialize_EIEnter && is_switching)) {
      robot_demo_DWork.HILInitialize_InitialEICounts[0] =
        robot_demo_P.HILInitialize_EIInitial;
      robot_demo_DWork.HILInitialize_InitialEICounts[1] =
        robot_demo_P.HILInitialize_EIInitial;
      robot_demo_DWork.HILInitialize_InitialEICounts[2] =
        robot_demo_P.HILInitialize_EIInitial;
      robot_demo_DWork.HILInitialize_InitialEICounts[3] =
        robot_demo_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(robot_demo_DWork.HILInitialize_Card,
        robot_demo_P.HILInitialize_EIChannels, 4U,
        &robot_demo_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(robot_demo_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_timebase_block): '<S2>/HIL Read Timebase' */

  /* S-Function Block: robot_demo/Encoders/HIL Read Timebase (hil_read_timebase_block) */
  {
    t_error result;
    result = hil_task_create_reader(robot_demo_DWork.HILInitialize_Card,
      robot_demo_P.HILReadTimebase_SamplesInBuffer,
      NULL, 0U,
      robot_demo_P.HILReadTimebase_EncoderChannels, 3U,
      NULL, 0U,
      NULL, 0U,
      &robot_demo_DWork.HILReadTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(robot_demo_M, _rt_error_message);
    }
  }

  MdlInitialize();
}

void MdlTerminate(void)
{
  robot_demo_terminate();
}

RT_MODEL_robot_demo *robot_demo(void)
{
  robot_demo_initialize(1);
  return robot_demo_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
