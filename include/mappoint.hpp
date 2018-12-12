//
// Created by lixin on 18-12-10.
//

#ifndef MAPPOINT_H
#define MAPPOINT_H

#include "common.hpp"

namespace PLXSLAM
{

    class Frame;
    class MapPoint
    {
    public:
        typedef shared_ptr<MapPoint> Ptr;
        unsigned long      id_;        // ID
        static unsigned long factory_id_;    // factory id
        bool        good_;      // wheter a good point
        Point3d    pos_;       // Position in world
        Point3d    norm_;      // Normal of viewing direction
        Mat         descriptor_; // Descriptor for matching

        list<Frame*>    observed_frames_;   // key-frames that can observe this point

        int         matched_times_;     // being an inliner in pose estimation
        int         visible_times_;     // being visible in current frame

        MapPoint();
        MapPoint(
                unsigned long id,
                const Point3d& position,
                const Point3d& norm,
                Frame* frame=nullptr,
                const Mat& descriptor=Mat()
        );

//        inline cv::Point3f getPositionCV() const {
//            return cv::Point3f( pos_(0,0), pos_(1,0), pos_(2,0) );
//        }

        static MapPoint::Ptr createMapPoint();
        static MapPoint::Ptr createMapPoint(
                const Point3d& pos_world,
                const Point3d& norm_,
                const Mat& descriptor,
                Frame* frame );
    };
}

#endif // MAPPOINT_H