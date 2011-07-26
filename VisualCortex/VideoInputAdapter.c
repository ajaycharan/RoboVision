#include "VideoInputAdapter.h"
#include "VisualCortex.h"
#include "VisionMemory.h"
#include "Precalculations.h"
#include "MovementRegistration.h"
#include "VisCortexFilters.h"
#include "VisCortexConvolutionFilters.h"
#include "FeatureExtraction.h"
#include "PatternRecognition.h"
#include "FeatureTracking.h"
#include "FaceDetection.h"
#include "StateSetting.h"
#include "IntegralImageConversion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 THIS FUNCTION IS CALLED EVERY TIME A NEW FRAME IS READY FOR STEREO VISION
*/
unsigned int PassNewFrameFromVideoInput(unsigned int input_img_regnum,unsigned int size_x,unsigned int size_y,unsigned int depth,unsigned char * rgbdata)
{
   if ( rgbdata == 0 ) { fprintf(stderr,"VisCortX_NewFrame given zero pointer"); return 0; }
   if ( input_img_regnum == LEFT_EYE )
    {

       video_register[input_img_regnum].lock=1;
       // FIRST STORE OLD REGISTERS
       VisCortX_CopyVideoRegister(LEFT_EYE,LAST_LEFT_EYE);
       VisCortX_CopyVideoRegister(EDGES_LEFT,LAST_EDGES_LEFT);
       VisCortX_CopyVideoRegister(SECOND_DERIVATIVE_LEFT,LAST_SECOND_DERIVATIVE_LEFT);
       VisCortX_CopyVideoRegister(MOVEMENT_LEFT,LAST_MOVEMENT_LEFT);

       // SECOND PASS NEW IMAGE
       VisCortx_WriteToVideoRegister(LEFT_EYE,size_x,size_y,depth,rgbdata);
       CalibrateImage(LEFT_EYE,CALIBRATED_LEFT_EYE,resection_left_precalc);

       // THIRD PROCESS NEW IMAGE  ( COMPRESSION )
       PrepareCleanSobeledGaussianAndDerivative(CALIBRATED_LEFT_EYE,EDGES_LEFT,SECOND_DERIVATIVE_LEFT,settings[DEPTHMAP_EDGE_LOW_STRICTNESS],settings[DEPTHMAP_EDGE_HIGH_STRICTNESS]);
       GenerateCompressHistogramOfImage(video_register[CALIBRATED_LEFT_EYE].pixels,l_video_register[HISTOGRAM_COMPRESSED_LEFT].pixels,metrics[HORIZONTAL_BUFFER],metrics[VERTICAL_BUFFER]);

        CopyRegister(EDGES_LEFT,GENERAL_3);
        PixelsOverThresholdSetAsOne(GENERAL_3,1);
        CompressRegister(GENERAL_3,EDGES_PRESENCE_GROUPED_LEFT);

        CompressRegister(MOVEMENT_LEFT,MOVEMENT_GROUPED_LEFT);
        CompressRegister(EDGES_LEFT,EDGES_GROUPED_LEFT);
        CompressRegister(SECOND_DERIVATIVE_LEFT,SECOND_DERIVATIVE_GROUPED_LEFT);


        VisCortx_Movement_Detection(1,0);
        TrackAllPointsOnRegisters(CALIBRATED_LEFT_EYE,LAST_LEFT_EYE,8000);

    } else
    if ( input_img_regnum == RIGHT_EYE )
    {

       video_register[input_img_regnum].lock=1;
       // FIRST STORE OLD REGISTERS
       VisCortX_CopyVideoRegister(RIGHT_EYE,LAST_RIGHT_EYE);
       VisCortX_CopyVideoRegister(EDGES_RIGHT,LAST_EDGES_RIGHT);
       VisCortX_CopyVideoRegister(SECOND_DERIVATIVE_RIGHT,LAST_SECOND_DERIVATIVE_RIGHT);
       VisCortX_CopyVideoRegister(MOVEMENT_RIGHT,LAST_MOVEMENT_RIGHT);

       // SECOND PASS NEW IMAGE
       VisCortx_WriteToVideoRegister(RIGHT_EYE,size_x,size_y,depth,rgbdata);
       CalibrateImage(RIGHT_EYE,CALIBRATED_RIGHT_EYE,resection_right_precalc);

       // THIRD PROCESS NEW IMAGE ( COMPRESSION )
       PrepareCleanSobeledGaussianAndDerivative(CALIBRATED_RIGHT_EYE,EDGES_RIGHT,SECOND_DERIVATIVE_RIGHT,settings[DEPTHMAP_EDGE_LOW_STRICTNESS],settings[DEPTHMAP_EDGE_HIGH_STRICTNESS]);
       GenerateCompressHistogramOfImage(video_register[CALIBRATED_RIGHT_EYE].pixels,l_video_register[HISTOGRAM_COMPRESSED_RIGHT].pixels,metrics[HORIZONTAL_BUFFER],metrics[VERTICAL_BUFFER]);

        CompressRegister(MOVEMENT_RIGHT,MOVEMENT_GROUPED_RIGHT);
        CompressRegister(EDGES_RIGHT,EDGES_GROUPED_RIGHT);
        CompressRegister(SECOND_DERIVATIVE_RIGHT,SECOND_DERIVATIVE_GROUPED_RIGHT);

        VisCortx_Movement_Detection(0,1);
        TrackAllPointsOnRegisters(CALIBRATED_RIGHT_EYE,LAST_RIGHT_EYE,8000);
    }




 return 1;
}
