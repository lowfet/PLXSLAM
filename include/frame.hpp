//
// Created by lixin on 18-12-10.
//

#ifndef FRAME_H
#define FRAME_H

#include "common.hpp"
#include "camera.hpp"

namespace PLXSLAM
{

// forward declare
    class MapPoint;
    class Frame
    {
    public:
        typedef std::shared_ptr<Frame> Ptr;
        unsigned long                  id_;         // id of this frame
        double                         time_stamp_; // when it is recorded
        Mat                            R_c_w_,t_c_w_;      // transform from world to camera
        Camera::Ptr                    camera_;     // Pinhole RGBD Camera model
        Mat                            color_, color_left_, color_right_, depth_; // color and depth image
//         std::vector<cv::KeyPoint>      keypoints_;  // key points in image
//         std::vector<MapPoint*>         map_points_; // associated map points
        bool                           is_key_frame_;  // whether a key-frame

    public: // data members
        Frame();
        Frame( long id, double time_stamp=0, Mat R_c_w=Mat(), Mat t_c_w=Mat(), Camera::Ptr camera=nullptr, Mat color=Mat() );
        ~Frame();

        static Frame::Ptr createFrame();

        // find the depth in depth map
        double findDepth( const cv::KeyPoint& kp );

        // check if a point is in this frame
        bool isInFrame( const Point3d& pt_world );

        // Get Camera Center
        Mat getCamCenter() const;

        void setPose( const Mat& R_c_w , const Mat& t_c_w );

    };

}

#endif // FRAME_H