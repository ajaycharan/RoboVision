#ifndef DISPARITYDEPTHMAP_HEURISTICS_H_INCLUDED
#define DISPARITYDEPTHMAP_HEURISTICS_H_INCLUDED



unsigned char InstantMovementDisparity(unsigned short *left_depth,unsigned short *right_depth);
unsigned char DisparityMapNormalize(unsigned short *left_depth,unsigned short *right_depth);
inline unsigned short FindNeighborDepth(
                                               unsigned short * full_depth_map,
                                               unsigned char * rgb_image,
                                               unsigned int search_area_stop,
                                               unsigned char r,unsigned char g,unsigned char b,
                                               unsigned int dpth_ptr,unsigned int img_ptr,
                                               unsigned int x,unsigned int y,unsigned int depth
                                       );
void EnhanceDepthMapWithEdges(unsigned char * rgb_image,unsigned short *full_depth_map,unsigned char * edges_map,unsigned int image_x,unsigned int image_y);
unsigned int EnhanceDepthMapFillHoles(unsigned char * rgb_image,unsigned short *full_depth_map,unsigned int image_x,unsigned int image_y);
int DepthMapToVideo(unsigned int depth_reg,unsigned int vid_reg);

#endif // DISPARITYDEPTHMAP_HEURISTICS_H_INCLUDED
