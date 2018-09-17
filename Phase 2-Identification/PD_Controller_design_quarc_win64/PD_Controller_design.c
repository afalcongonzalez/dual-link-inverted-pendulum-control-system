/*
 * PD_Controller_design.c
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
#include "PD_Controller_design.h"
#include "PD_Controller_design_private.h"
#include "PD_Controller_design_dt.h"

/* Block signals (auto storage) */
BlockIO_PD_Controller_design PD_Controller_design_B;

/* Block states (auto storage) */
D_Work_PD_Controller_design PD_Controller_design_DWork;

/* Real-time model */
RT_MODEL_PD_Controller_design PD_Controller_design_M_;
RT_MODEL_PD_Controller_design *const PD_Controller_design_M =
  &PD_Controller_design_M_;

/* Model output function */
void PD_Controller_design_output(int_T tid)
{
  /* S-Function (hil_read_timebase_block): '<S4>/HIL Read Timebase' */

  /* S-Function Block: PD_Controller_design/Robot/Encoders/HIL Read Timebase (hil_read_timebase_block) */
  {
    t_error result;
    result = hil_task_read(PD_Controller_design_DWork.HILReadTimebase_Task, 1,
      NULL,
      &PD_Controller_design_DWork.HILReadTimebase_EncoderBuffer[0],
      NULL,
      NULL
      );
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
    } else {
      PD_Controller_design_B.HILReadTimebase[0] =
        PD_Controller_design_DWork.HILReadTimebase_EncoderBuffer[0];
      PD_Controller_design_B.HILReadTimebase[1] =
        PD_Controller_design_DWork.HILReadTimebase_EncoderBuffer[1];
      PD_Controller_design_B.HILReadTimebase[2] =
        PD_Controller_design_DWork.HILReadTimebase_EncoderBuffer[2];
    }
  }

  /* Switch: '<S4>/Switch' incorporates:
   *  Constant: '<S4>/Constant1'
   */
  if (PD_Controller_design_P.Constant1_Value >
      PD_Controller_design_P.Switch_Threshold) {
    /* Gain: '<S4>/gain t1 for 2dPanto new' */
    PD_Controller_design_B.gaint1for2dPantonew =
      PD_Controller_design_P.gaint1for2dPantonew_Gain *
      PD_Controller_design_B.HILReadTimebase[0];
    PD_Controller_design_B.Switch = PD_Controller_design_B.gaint1for2dPantonew;
  } else {
    /* Gain: '<S4>/gain t1 for 2dPanto' */
    PD_Controller_design_B.gaint1for2dPanto =
      PD_Controller_design_P.gaint1for2dPanto_Gain *
      PD_Controller_design_B.HILReadTimebase[0];
    PD_Controller_design_B.Switch = PD_Controller_design_B.gaint1for2dPanto;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/Constant2'
   */
  PD_Controller_design_B.Sum = PD_Controller_design_B.Switch +
    PD_Controller_design_P.Constant2_Value;

  /* Sin: '<Root>/Sine Wave2' */
  PD_Controller_design_B.SineWave2 = sin(PD_Controller_design_P.SineWave2_Freq *
    PD_Controller_design_M->Timing.t[0] + PD_Controller_design_P.SineWave2_Phase)
    * PD_Controller_design_P.SineWave2_Amp +
    PD_Controller_design_P.SineWave2_Bias;

  /* Sum: '<Root>/Sum' */
  PD_Controller_design_B.Sum_m = PD_Controller_design_B.SineWave2 -
    PD_Controller_design_B.Sum;

  /* Gain: '<S2>/Gain' */
  PD_Controller_design_B.Gain = PD_Controller_design_P.Gain_Gain *
    PD_Controller_design_B.Sum_m;

  /* Derivative: '<S2>/Derivative' */
  {
    real_T t = PD_Controller_design_M->Timing.t[0];
    real_T timeStampA = PD_Controller_design_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = PD_Controller_design_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &PD_Controller_design_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      PD_Controller_design_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &PD_Controller_design_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &PD_Controller_design_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      PD_Controller_design_B.Derivative = (PD_Controller_design_B.Sum_m - *lastU
        ++) / deltaT;
    }
  }

  /* Gain: '<S2>/Gain1' */
  PD_Controller_design_B.Gain1 = PD_Controller_design_P.Gain1_Gain *
    PD_Controller_design_B.Derivative;

  /* Sum: '<S2>/Sum1' */
  PD_Controller_design_B.Sum1 = PD_Controller_design_B.Gain +
    PD_Controller_design_B.Gain1;

  /* Sum: '<S3>/Add' incorporates:
   *  Constant: '<S3>/Constant'
   */
  PD_Controller_design_B.Add[0] = PD_Controller_design_P.Constant_Value +
    PD_Controller_design_B.Sum1;
  PD_Controller_design_B.Add[1] = PD_Controller_design_P.Constant_Value +
    PD_Controller_design_B.Sum1;

  /* Switch: '<S3>/Switch' incorporates:
   *  Constant: '<S3>/Constant1'
   */
  if (PD_Controller_design_P.Constant1_Value_e >
      PD_Controller_design_P.Switch_Threshold_l) {
    /* Gain: '<S3>/gain for 2DPanto new amplifier' */
    PD_Controller_design_B.gainfor2DPantonewamplifier[0] =
      PD_Controller_design_P.gainfor2DPantonewamplifier_Gain *
      PD_Controller_design_B.Add[0];
    PD_Controller_design_B.gainfor2DPantonewamplifier[1] =
      PD_Controller_design_P.gainfor2DPantonewamplifier_Gain *
      PD_Controller_design_B.Add[1];
    PD_Controller_design_B.Switch_a[0] =
      PD_Controller_design_B.gainfor2DPantonewamplifier[0];
    PD_Controller_design_B.Switch_a[1] =
      PD_Controller_design_B.gainfor2DPantonewamplifier[1];
  } else {
    /* Gain: '<S3>/gain for 2DPanto amplifier' */
    PD_Controller_design_B.gainfor2DPantoamplifier[0] =
      PD_Controller_design_P.gainfor2DPantoamplifier_Gain *
      PD_Controller_design_B.Add[0];
    PD_Controller_design_B.gainfor2DPantoamplifier[1] =
      PD_Controller_design_P.gainfor2DPantoamplifier_Gain *
      PD_Controller_design_B.Add[1];
    PD_Controller_design_B.Switch_a[0] =
      PD_Controller_design_B.gainfor2DPantoamplifier[0];
    PD_Controller_design_B.Switch_a[1] =
      PD_Controller_design_B.gainfor2DPantoamplifier[1];
  }

  /* End of Switch: '<S3>/Switch' */

  /* Gain: '<S3>/K1' */
  PD_Controller_design_B.K1[0] = PD_Controller_design_P.K1_Gain[0] *
    PD_Controller_design_B.Switch_a[0];
  PD_Controller_design_B.K1[1] = PD_Controller_design_P.K1_Gain[1] *
    PD_Controller_design_B.Switch_a[1];

  /* S-Function (hil_write_analog_block): '<S3>/HIL Write Analog' */

  /* S-Function Block: PD_Controller_design/Robot/2Dpanto motor/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(PD_Controller_design_DWork.HILInitialize_Card,
      PD_Controller_design_P.HILWriteAnalog_Channels, 2,
      PD_Controller_design_B.K1);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
    }
  }

  /* S-Function (hil_write_digital_block): '<S3>/HIL Write Digital' */

  /* S-Function Block: PD_Controller_design/Robot/2Dpanto motor/HIL Write Digital (hil_write_digital_block) */
  {
    t_error result;
    PD_Controller_design_DWork.HILWriteDigital_Buffer[0] =
      (PD_Controller_design_P.Constant_Value_a[0] != 0);
    PD_Controller_design_DWork.HILWriteDigital_Buffer[1] =
      (PD_Controller_design_P.Constant_Value_a[1] != 0);
    PD_Controller_design_DWork.HILWriteDigital_Buffer[2] =
      (PD_Controller_design_P.Constant_Value_a[2] != 0);
    PD_Controller_design_DWork.HILWriteDigital_Buffer[3] =
      (PD_Controller_design_P.Constant_Value_a[3] != 0);
    result = hil_write_digital(PD_Controller_design_DWork.HILInitialize_Card,
      PD_Controller_design_P.HILWriteDigital_Channels, 4,
      &PD_Controller_design_DWork.HILWriteDigital_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
    }
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void PD_Controller_design_update(int_T tid)
{
  /* Update for Derivative: '<S2>/Derivative' */
  {
    real_T timeStampA = PD_Controller_design_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = PD_Controller_design_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &PD_Controller_design_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &PD_Controller_design_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &PD_Controller_design_DWork.Derivative_RWORK.TimeStampB;
        lastU = &PD_Controller_design_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &PD_Controller_design_DWork.Derivative_RWORK.TimeStampB;
        lastU = &PD_Controller_design_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = PD_Controller_design_M->Timing.t[0];
    *lastU++ = PD_Controller_design_B.Sum_m;
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++PD_Controller_design_M->Timing.clockTick0)) {
    ++PD_Controller_design_M->Timing.clockTickH0;
  }

  PD_Controller_design_M->Timing.t[0] =
    PD_Controller_design_M->Timing.clockTick0 *
    PD_Controller_design_M->Timing.stepSize0 +
    PD_Controller_design_M->Timing.clockTickH0 *
    PD_Controller_design_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++PD_Controller_design_M->Timing.clockTick1)) {
      ++PD_Controller_design_M->Timing.clockTickH1;
    }

    PD_Controller_design_M->Timing.t[1] =
      PD_Controller_design_M->Timing.clockTick1 *
      PD_Controller_design_M->Timing.stepSize1 +
      PD_Controller_design_M->Timing.clockTickH1 *
      PD_Controller_design_M->Timing.stepSize1 * 4294967296.0;
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model initialize function */
void PD_Controller_design_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)PD_Controller_design_M, 0,
                sizeof(RT_MODEL_PD_Controller_design));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PD_Controller_design_M->solverInfo,
                          &PD_Controller_design_M->Timing.simTimeStep);
    rtsiSetTPtr(&PD_Controller_design_M->solverInfo, &rtmGetTPtr
                (PD_Controller_design_M));
    rtsiSetStepSizePtr(&PD_Controller_design_M->solverInfo,
                       &PD_Controller_design_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&PD_Controller_design_M->solverInfo,
                          (&rtmGetErrorStatus(PD_Controller_design_M)));
    rtsiSetRTModelPtr(&PD_Controller_design_M->solverInfo,
                      PD_Controller_design_M);
  }

  rtsiSetSimTimeStep(&PD_Controller_design_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&PD_Controller_design_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = PD_Controller_design_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    PD_Controller_design_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    PD_Controller_design_M->Timing.sampleTimes =
      (&PD_Controller_design_M->Timing.sampleTimesArray[0]);
    PD_Controller_design_M->Timing.offsetTimes =
      (&PD_Controller_design_M->Timing.offsetTimesArray[0]);

    /* task periods */
    PD_Controller_design_M->Timing.sampleTimes[0] = (0.0);
    PD_Controller_design_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    PD_Controller_design_M->Timing.offsetTimes[0] = (0.0);
    PD_Controller_design_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(PD_Controller_design_M, &PD_Controller_design_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = PD_Controller_design_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    PD_Controller_design_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(PD_Controller_design_M, 30.0);
  PD_Controller_design_M->Timing.stepSize0 = 0.001;
  PD_Controller_design_M->Timing.stepSize1 = 0.001;

  /* external mode info */
  PD_Controller_design_M->Sizes.checksums[0] = (1514765927U);
  PD_Controller_design_M->Sizes.checksums[1] = (876192862U);
  PD_Controller_design_M->Sizes.checksums[2] = (1512313180U);
  PD_Controller_design_M->Sizes.checksums[3] = (2263832521U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    PD_Controller_design_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(PD_Controller_design_M->extModeInfo,
      &PD_Controller_design_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(PD_Controller_design_M->extModeInfo,
                        PD_Controller_design_M->Sizes.checksums);
    rteiSetTPtr(PD_Controller_design_M->extModeInfo, rtmGetTPtr
                (PD_Controller_design_M));
  }

  PD_Controller_design_M->solverInfoPtr = (&PD_Controller_design_M->solverInfo);
  PD_Controller_design_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&PD_Controller_design_M->solverInfo, 0.001);
  rtsiSetSolverMode(&PD_Controller_design_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  PD_Controller_design_M->ModelData.blockIO = ((void *) &PD_Controller_design_B);

  {
    PD_Controller_design_B.HILReadTimebase[0] = 0.0;
    PD_Controller_design_B.HILReadTimebase[1] = 0.0;
    PD_Controller_design_B.HILReadTimebase[2] = 0.0;
    PD_Controller_design_B.Switch = 0.0;
    PD_Controller_design_B.Sum = 0.0;
    PD_Controller_design_B.SineWave2 = 0.0;
    PD_Controller_design_B.Sum_m = 0.0;
    PD_Controller_design_B.Gain = 0.0;
    PD_Controller_design_B.Derivative = 0.0;
    PD_Controller_design_B.Gain1 = 0.0;
    PD_Controller_design_B.Sum1 = 0.0;
    PD_Controller_design_B.Add[0] = 0.0;
    PD_Controller_design_B.Add[1] = 0.0;
    PD_Controller_design_B.Switch_a[0] = 0.0;
    PD_Controller_design_B.Switch_a[1] = 0.0;
    PD_Controller_design_B.K1[0] = 0.0;
    PD_Controller_design_B.K1[1] = 0.0;
    PD_Controller_design_B.gaint1for2dPantonew = 0.0;
    PD_Controller_design_B.gaint1for2dPanto = 0.0;
    PD_Controller_design_B.gainfor2DPantonewamplifier[0] = 0.0;
    PD_Controller_design_B.gainfor2DPantonewamplifier[1] = 0.0;
    PD_Controller_design_B.gainfor2DPantoamplifier[0] = 0.0;
    PD_Controller_design_B.gainfor2DPantoamplifier[1] = 0.0;
  }

  /* parameters */
  PD_Controller_design_M->ModelData.defaultParam = ((real_T *)
    &PD_Controller_design_P);

  /* states (dwork) */
  PD_Controller_design_M->Work.dwork = ((void *) &PD_Controller_design_DWork);
  (void) memset((void *)&PD_Controller_design_DWork, 0,
                sizeof(D_Work_PD_Controller_design));
  PD_Controller_design_DWork.HILInitialize_AIMinimums[0] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AIMinimums[1] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AIMinimums[2] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AIMinimums[3] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AIMaximums[0] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AIMaximums[1] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AIMaximums[2] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AIMaximums[3] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOMinimums[0] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOMinimums[1] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOMinimums[2] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOMinimums[3] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOMaximums[0] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOMaximums[1] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOMaximums[2] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOMaximums[3] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOVoltages[0] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOVoltages[1] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOVoltages[2] = 0.0;
  PD_Controller_design_DWork.HILInitialize_AOVoltages[3] = 0.0;
  PD_Controller_design_DWork.HILInitialize_FilterFrequency[0] = 0.0;
  PD_Controller_design_DWork.HILInitialize_FilterFrequency[1] = 0.0;
  PD_Controller_design_DWork.HILInitialize_FilterFrequency[2] = 0.0;
  PD_Controller_design_DWork.HILInitialize_FilterFrequency[3] = 0.0;
  PD_Controller_design_DWork.Derivative_RWORK.TimeStampA = 0.0;
  PD_Controller_design_DWork.Derivative_RWORK.LastUAtTimeA = 0.0;
  PD_Controller_design_DWork.Derivative_RWORK.TimeStampB = 0.0;
  PD_Controller_design_DWork.Derivative_RWORK.LastUAtTimeB = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    PD_Controller_design_M->SpecialInfo.mappingInfo = (&dtInfo);
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
void PD_Controller_design_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: PD_Controller_design/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    hil_task_stop_all(PD_Controller_design_DWork.HILInitialize_Card);
    hil_monitor_stop_all(PD_Controller_design_DWork.HILInitialize_Card);
    is_switching = false;
    if ((PD_Controller_design_P.HILInitialize_AOTerminate && !is_switching) ||
        (PD_Controller_design_P.HILInitialize_AOExit && is_switching)) {
      PD_Controller_design_DWork.HILInitialize_AOVoltages[0] =
        PD_Controller_design_P.HILInitialize_AOFinal;
      PD_Controller_design_DWork.HILInitialize_AOVoltages[1] =
        PD_Controller_design_P.HILInitialize_AOFinal;
      PD_Controller_design_DWork.HILInitialize_AOVoltages[2] =
        PD_Controller_design_P.HILInitialize_AOFinal;
      PD_Controller_design_DWork.HILInitialize_AOVoltages[3] =
        PD_Controller_design_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 4U;
    }

    if ((PD_Controller_design_P.HILInitialize_DOTerminate && !is_switching) ||
        (PD_Controller_design_P.HILInitialize_DOExit && is_switching)) {
      PD_Controller_design_DWork.HILInitialize_DOBits[0] =
        PD_Controller_design_P.HILInitialize_DOFinal;
      PD_Controller_design_DWork.HILInitialize_DOBits[1] =
        PD_Controller_design_P.HILInitialize_DOFinal;
      PD_Controller_design_DWork.HILInitialize_DOBits[2] =
        PD_Controller_design_P.HILInitialize_DOFinal;
      PD_Controller_design_DWork.HILInitialize_DOBits[3] =
        PD_Controller_design_P.HILInitialize_DOFinal;
      num_final_digital_outputs = 4U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(PD_Controller_design_DWork.HILInitialize_Card
                         , PD_Controller_design_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , PD_Controller_design_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &PD_Controller_design_DWork.HILInitialize_AOVoltages
                         [0]
                         , NULL
                         , &PD_Controller_design_DWork.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (PD_Controller_design_DWork.HILInitialize_Card,
             PD_Controller_design_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &PD_Controller_design_DWork.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (PD_Controller_design_DWork.HILInitialize_Card,
             PD_Controller_design_P.HILInitialize_DOChannels,
             num_final_digital_outputs,
             &PD_Controller_design_DWork.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(PD_Controller_design_DWork.HILInitialize_Card);
    hil_monitor_delete_all(PD_Controller_design_DWork.HILInitialize_Card);
    hil_close(PD_Controller_design_DWork.HILInitialize_Card);
    PD_Controller_design_DWork.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  PD_Controller_design_output(tid);
}

void MdlUpdate(int_T tid)
{
  PD_Controller_design_update(tid);
}

void MdlInitializeSizes(void)
{
  PD_Controller_design_M->Sizes.numContStates = (0);/* Number of continuous states */
  PD_Controller_design_M->Sizes.numY = (0);/* Number of model outputs */
  PD_Controller_design_M->Sizes.numU = (0);/* Number of model inputs */
  PD_Controller_design_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  PD_Controller_design_M->Sizes.numSampTimes = (2);/* Number of sample times */
  PD_Controller_design_M->Sizes.numBlocks = (30);/* Number of blocks */
  PD_Controller_design_M->Sizes.numBlockIO = (16);/* Number of block outputs */
  PD_Controller_design_M->Sizes.numBlockPrms = (110);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for Derivative: '<S2>/Derivative' */
  PD_Controller_design_DWork.Derivative_RWORK.TimeStampA = rtInf;
  PD_Controller_design_DWork.Derivative_RWORK.TimeStampB = rtInf;
}

void MdlStart(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: PD_Controller_design/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q4", "0", &PD_Controller_design_DWork.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
      return;
    }

    is_switching = false;
    if ((PD_Controller_design_P.HILInitialize_CKPStart && !is_switching) ||
        (PD_Controller_design_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(PD_Controller_design_DWork.HILInitialize_Card,
                                  (t_clock *)
        PD_Controller_design_P.HILInitialize_CKChannels, 2U, (t_clock_mode *)
        PD_Controller_design_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(PD_Controller_design_DWork.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
      return;
    }

    if ((PD_Controller_design_P.HILInitialize_AIPStart && !is_switching) ||
        (PD_Controller_design_P.HILInitialize_AIPEnter && is_switching)) {
      PD_Controller_design_DWork.HILInitialize_AIMinimums[0] =
        PD_Controller_design_P.HILInitialize_AILow;
      PD_Controller_design_DWork.HILInitialize_AIMinimums[1] =
        PD_Controller_design_P.HILInitialize_AILow;
      PD_Controller_design_DWork.HILInitialize_AIMinimums[2] =
        PD_Controller_design_P.HILInitialize_AILow;
      PD_Controller_design_DWork.HILInitialize_AIMinimums[3] =
        PD_Controller_design_P.HILInitialize_AILow;
      PD_Controller_design_DWork.HILInitialize_AIMaximums[0] =
        PD_Controller_design_P.HILInitialize_AIHigh;
      PD_Controller_design_DWork.HILInitialize_AIMaximums[1] =
        PD_Controller_design_P.HILInitialize_AIHigh;
      PD_Controller_design_DWork.HILInitialize_AIMaximums[2] =
        PD_Controller_design_P.HILInitialize_AIHigh;
      PD_Controller_design_DWork.HILInitialize_AIMaximums[3] =
        PD_Controller_design_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (PD_Controller_design_DWork.HILInitialize_Card,
         PD_Controller_design_P.HILInitialize_AIChannels, 4U,
         &PD_Controller_design_DWork.HILInitialize_AIMinimums[0],
         &PD_Controller_design_DWork.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }
    }

    if ((PD_Controller_design_P.HILInitialize_AOPStart && !is_switching) ||
        (PD_Controller_design_P.HILInitialize_AOPEnter && is_switching)) {
      PD_Controller_design_DWork.HILInitialize_AOMinimums[0] =
        PD_Controller_design_P.HILInitialize_AOLow;
      PD_Controller_design_DWork.HILInitialize_AOMinimums[1] =
        PD_Controller_design_P.HILInitialize_AOLow;
      PD_Controller_design_DWork.HILInitialize_AOMinimums[2] =
        PD_Controller_design_P.HILInitialize_AOLow;
      PD_Controller_design_DWork.HILInitialize_AOMinimums[3] =
        PD_Controller_design_P.HILInitialize_AOLow;
      PD_Controller_design_DWork.HILInitialize_AOMaximums[0] =
        PD_Controller_design_P.HILInitialize_AOHigh;
      PD_Controller_design_DWork.HILInitialize_AOMaximums[1] =
        PD_Controller_design_P.HILInitialize_AOHigh;
      PD_Controller_design_DWork.HILInitialize_AOMaximums[2] =
        PD_Controller_design_P.HILInitialize_AOHigh;
      PD_Controller_design_DWork.HILInitialize_AOMaximums[3] =
        PD_Controller_design_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (PD_Controller_design_DWork.HILInitialize_Card,
         PD_Controller_design_P.HILInitialize_AOChannels, 4U,
         &PD_Controller_design_DWork.HILInitialize_AOMinimums[0],
         &PD_Controller_design_DWork.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }
    }

    if ((PD_Controller_design_P.HILInitialize_AOStart && !is_switching) ||
        (PD_Controller_design_P.HILInitialize_AOEnter && is_switching)) {
      PD_Controller_design_DWork.HILInitialize_AOVoltages[0] =
        PD_Controller_design_P.HILInitialize_AOInitial;
      PD_Controller_design_DWork.HILInitialize_AOVoltages[1] =
        PD_Controller_design_P.HILInitialize_AOInitial;
      PD_Controller_design_DWork.HILInitialize_AOVoltages[2] =
        PD_Controller_design_P.HILInitialize_AOInitial;
      PD_Controller_design_DWork.HILInitialize_AOVoltages[3] =
        PD_Controller_design_P.HILInitialize_AOInitial;
      result = hil_write_analog(PD_Controller_design_DWork.HILInitialize_Card,
        PD_Controller_design_P.HILInitialize_AOChannels, 4U,
        &PD_Controller_design_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }
    }

    if (PD_Controller_design_P.HILInitialize_AOReset) {
      PD_Controller_design_DWork.HILInitialize_AOVoltages[0] =
        PD_Controller_design_P.HILInitialize_AOWatchdog;
      PD_Controller_design_DWork.HILInitialize_AOVoltages[1] =
        PD_Controller_design_P.HILInitialize_AOWatchdog;
      PD_Controller_design_DWork.HILInitialize_AOVoltages[2] =
        PD_Controller_design_P.HILInitialize_AOWatchdog;
      PD_Controller_design_DWork.HILInitialize_AOVoltages[3] =
        PD_Controller_design_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (PD_Controller_design_DWork.HILInitialize_Card,
         PD_Controller_design_P.HILInitialize_AOChannels, 4U,
         &PD_Controller_design_DWork.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions
      (PD_Controller_design_DWork.HILInitialize_Card, NULL, 0U,
       PD_Controller_design_P.HILInitialize_DOChannels, 4U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
      return;
    }

    if ((PD_Controller_design_P.HILInitialize_DOStart && !is_switching) ||
        (PD_Controller_design_P.HILInitialize_DOEnter && is_switching)) {
      PD_Controller_design_DWork.HILInitialize_DOBits[0] =
        PD_Controller_design_P.HILInitialize_DOInitial;
      PD_Controller_design_DWork.HILInitialize_DOBits[1] =
        PD_Controller_design_P.HILInitialize_DOInitial;
      PD_Controller_design_DWork.HILInitialize_DOBits[2] =
        PD_Controller_design_P.HILInitialize_DOInitial;
      PD_Controller_design_DWork.HILInitialize_DOBits[3] =
        PD_Controller_design_P.HILInitialize_DOInitial;
      result = hil_write_digital(PD_Controller_design_DWork.HILInitialize_Card,
        PD_Controller_design_P.HILInitialize_DOChannels, 4U, (t_boolean *)
        &PD_Controller_design_DWork.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }
    }

    if (PD_Controller_design_P.HILInitialize_DOReset) {
      PD_Controller_design_DWork.HILInitialize_DOStates[0] =
        PD_Controller_design_P.HILInitialize_DOWatchdog;
      PD_Controller_design_DWork.HILInitialize_DOStates[1] =
        PD_Controller_design_P.HILInitialize_DOWatchdog;
      PD_Controller_design_DWork.HILInitialize_DOStates[2] =
        PD_Controller_design_P.HILInitialize_DOWatchdog;
      PD_Controller_design_DWork.HILInitialize_DOStates[3] =
        PD_Controller_design_P.HILInitialize_DOWatchdog;
      result = hil_watchdog_set_digital_expiration_state
        (PD_Controller_design_DWork.HILInitialize_Card,
         PD_Controller_design_P.HILInitialize_DOChannels, 4U, (const
          t_digital_state *) &PD_Controller_design_DWork.HILInitialize_DOStates
         [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }
    }

    if ((PD_Controller_design_P.HILInitialize_EIPStart && !is_switching) ||
        (PD_Controller_design_P.HILInitialize_EIPEnter && is_switching)) {
      PD_Controller_design_DWork.HILInitialize_QuadratureModes[0] =
        PD_Controller_design_P.HILInitialize_EIQuadrature;
      PD_Controller_design_DWork.HILInitialize_QuadratureModes[1] =
        PD_Controller_design_P.HILInitialize_EIQuadrature;
      PD_Controller_design_DWork.HILInitialize_QuadratureModes[2] =
        PD_Controller_design_P.HILInitialize_EIQuadrature;
      PD_Controller_design_DWork.HILInitialize_QuadratureModes[3] =
        PD_Controller_design_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (PD_Controller_design_DWork.HILInitialize_Card,
         PD_Controller_design_P.HILInitialize_EIChannels, 4U,
         (t_encoder_quadrature_mode *)
         &PD_Controller_design_DWork.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }

      PD_Controller_design_DWork.HILInitialize_FilterFrequency[0] =
        PD_Controller_design_P.HILInitialize_EIFrequency;
      PD_Controller_design_DWork.HILInitialize_FilterFrequency[1] =
        PD_Controller_design_P.HILInitialize_EIFrequency;
      PD_Controller_design_DWork.HILInitialize_FilterFrequency[2] =
        PD_Controller_design_P.HILInitialize_EIFrequency;
      PD_Controller_design_DWork.HILInitialize_FilterFrequency[3] =
        PD_Controller_design_P.HILInitialize_EIFrequency;
      result = hil_set_encoder_filter_frequency
        (PD_Controller_design_DWork.HILInitialize_Card,
         PD_Controller_design_P.HILInitialize_EIChannels, 4U,
         &PD_Controller_design_DWork.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }
    }

    if ((PD_Controller_design_P.HILInitialize_EIStart && !is_switching) ||
        (PD_Controller_design_P.HILInitialize_EIEnter && is_switching)) {
      PD_Controller_design_DWork.HILInitialize_InitialEICounts[0] =
        PD_Controller_design_P.HILInitialize_EIInitial;
      PD_Controller_design_DWork.HILInitialize_InitialEICounts[1] =
        PD_Controller_design_P.HILInitialize_EIInitial;
      PD_Controller_design_DWork.HILInitialize_InitialEICounts[2] =
        PD_Controller_design_P.HILInitialize_EIInitial;
      PD_Controller_design_DWork.HILInitialize_InitialEICounts[3] =
        PD_Controller_design_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts
        (PD_Controller_design_DWork.HILInitialize_Card,
         PD_Controller_design_P.HILInitialize_EIChannels, 4U,
         &PD_Controller_design_DWork.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_timebase_block): '<S4>/HIL Read Timebase' */

  /* S-Function Block: PD_Controller_design/Robot/Encoders/HIL Read Timebase (hil_read_timebase_block) */
  {
    t_error result;
    result = hil_task_create_reader
      (PD_Controller_design_DWork.HILInitialize_Card,
       PD_Controller_design_P.HILReadTimebase_SamplesInBuffer,
       NULL, 0U,
       PD_Controller_design_P.HILReadTimebase_EncoderChannels, 3U,
       NULL, 0U,
       NULL, 0U,
       &PD_Controller_design_DWork.HILReadTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(PD_Controller_design_M, _rt_error_message);
    }
  }

  MdlInitialize();
}

void MdlTerminate(void)
{
  PD_Controller_design_terminate();
}

RT_MODEL_PD_Controller_design *PD_Controller_design(void)
{
  PD_Controller_design_initialize(1);
  return PD_Controller_design_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
